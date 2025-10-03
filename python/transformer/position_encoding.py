"""
Spike-Based Positional Encoding for SNNs.

This module provides functions to create spike-based positional encodings,
suitable for use in Spiking Neural Network models, particularly those
built with Brian2. It uses sinusoidal position encoding, similar to
the method used in Transformer models, and converts these encodings
into spike trains using Poisson neurons.
"""

import numpy as np
from brian2 import NeuronGroup, PoissonGroup, Hz, SpikeMonitor, run, figure, show, ms
import matplotlib.pyplot as plt

def get_positional_encoding(positions: np.ndarray, d_pos: int) -> np.ndarray:
    """
    Calculates sinusoidal positional encoding for 2D positions.

    Args:
        positions (np.ndarray): An array of shape (num_patches, 2) with (x, y) coordinates.
        d_pos (int): The dimension of the positional encoding. Must be an even number
                     to accommodate separate encodings for x and y.

    Returns:
        np.ndarray: A (num_patches, d_pos) array of positional encodings.
    """
    if d_pos % 4 != 0:
        raise ValueError("d_pos must be a multiple of 4 to ensure d_half is even for sin/cos pairs.")

    num_patches = positions.shape[0]
    d_half = d_pos // 2

    # Term for calculating frequencies
    inv_freq = 1. / (10000 ** (np.arange(0, d_half, 2, dtype=np.float64) / d_half))

    # Extract x and y positions
    pos_x = positions[:, 0:1]
    pos_y = positions[:, 1:2]

    # Calculate sine and cosine components for x and y
    sin_inp_x = pos_x * inv_freq
    sin_inp_y = pos_y * inv_freq

    emb_x = np.zeros((num_patches, d_half))
    emb_x[:, 0::2] = np.sin(sin_inp_x)
    emb_x[:, 1::2] = np.cos(sin_inp_x)

    emb_y = np.zeros((num_patches, d_half))
    emb_y[:, 0::2] = np.sin(sin_inp_y)
    emb_y[:, 1::2] = np.cos(sin_inp_y)

    # Concatenate x and y encodings
    pe = np.concatenate([emb_x, emb_y], axis=-1)
    return pe

def create_spike_based_position_encoding(patches: list | np.ndarray, d_pos: int, max_rate: float = 100.0) -> PoissonGroup:
    """
    Creates a population of neurons that generate spike-based positional encodings.

    For each patch Pj, a dedicated population of Dpos Poisson neurons is established.
    The continuous values of the sinusoidal position encoding vector (pej) are
    converted into spike trains where the firing rate of each neuron is directly
    proportional to its corresponding scaled value in the pej vector.

    Args:
        patches (list or np.ndarray): A list or array of (x, y) coordinates for each patch.
        d_pos (int): The dimension of the positional encoding vector for each patch.
        max_rate (float): The maximum firing rate of the encoding neurons in Hz.

    Returns:
        brian2.PoissonGroup: A group of neurons firing with rates proportional to the positional encoding.
    """
    if not isinstance(patches, np.ndarray):
        patches = np.array(patches)

    num_patches = len(patches)
    total_neurons = num_patches * d_pos

    # 1. Calculate the continuous-valued positional encoding vectors
    pe_vectors = get_positional_encoding(patches, d_pos)  # Shape: (num_patches, d_pos)

    # 2. Scale the PE values (from [-1, 1]) to a positive firing rate [0, max_rate]
    # A value of -1 maps to 0 Hz, 0 maps to max_rate/2, and 1 maps to max_rate.
    scaled_rates = (pe_vectors + 1) / 2 * max_rate

    # 3. Flatten the rates to a 1D array for the PoissonGroup
    rates_flat = scaled_rates.flatten()

    # 4. Create the PoissonGroup
    position_encoding_neurons = PoissonGroup(total_neurons, rates=rates_flat * Hz)

    return position_encoding_neurons

if __name__ == '__main__':
    # This is an example of how to use the position encoding module.
    # It is not part of the main model but serves for demonstration and testing.

    # Example: 4x4 grid of patches (16 patches)
    patch_coords = []
    for y in range(5):
        for x in range(5):
            patch_coords.append((x, y))

    D_pos = 12  # Dimension of position encoding

    print(f"Number of patches: {len(patch_coords)}")
    print(f"Positional Encoding Dimension: {D_pos}")

    # Create the PE neuron group
    pe_neurons = create_spike_based_position_encoding(patch_coords, D_pos, max_rate=100.0)

    # Monitor spikes from the PE neurons
    spike_monitor = SpikeMonitor(pe_neurons)

    # Run the simulation for a short period
    simulation_time = 500 * ms
    run(simulation_time)

    # --- Plotting Results ---
    figure(figsize=(12, 8))

    # Plot spike raster
    plt.subplot(2, 1, 1)
    plt.plot(spike_monitor.t / ms, spike_monitor.i, '.k', markersize=2)
    plt.xlabel('Time (ms)')
    plt.ylabel('Neuron Index')
    plt.title(f'Spike Raster of {D_pos}-D Positional Encoding for {len(patch_coords)} Patches')
    plt.grid(True, which='both', linestyle='--', linewidth=0.5)

    # Plot firing rates
    # Each group of D_pos neurons corresponds to a patch
    rates = np.array(pe_neurons.rates / Hz).reshape((len(patch_coords), D_pos))
    plt.subplot(2, 1, 2)
    im = plt.imshow(rates, aspect='auto', interpolation='nearest', cmap='viridis')
    plt.xlabel('PE Dimension')
    plt.ylabel('Patch Index')
    plt.title('Firing Rates of PE Neurons per Patch')
    plt.colorbar(im, label='Firing Rate (Hz)')

    plt.tight_layout()
    show()
