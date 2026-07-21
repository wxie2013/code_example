
#!/bin/bash

# Array of directories to back up
folders=(
    "/scratch/bell/mstojano/d0outputs_new_07a"
    "/scratch/bell/mstojano/forHoney_07a"
    "/scratch/bell/mstojano/forSoumik_04a"
    "/scratch/bell/mstojano/hepdata_05"
    "/scratch/bell/mstojano/homeBrown_07a"
    "/scratch/bell/mstojano/homehammerold_07a"
    "/scratch/bell/mstojano/INTT_2026"
    "/scratch/bell/mstojano/LambdaC_flow_07a"
    "/scratch/bell/mstojano/Run3_04"
    "/scratch/bell/mstojano/tmpFolder_07a"
    "/scratch/bell/mstojano/tmphadoopbackup_04a"
    "/scratch/bell/mstojano/XeXe_07a"
)

# Loop over each path
for path in "${folders[@]}"; do
    # Extract just the folder name (e.g., "d0outputs_new_07a")
    folder_name=$(basename "$path")
    
    echo "Archiving $folder_name via hsi..."
    
    # Run the hsi command from the parent directory of the target folder
    # so that 'put -R' finds the local folder correctly.
    cd "$(dirname "$path")" && hsi "cd /group/wxie/Milan/BELL_scratch; put -R $folder_name" &> "/home/wxie/out_$folder_name"
done

echo "All transfers completed."
