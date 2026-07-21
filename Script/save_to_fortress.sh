#!/bin/bash

# Array of directories to back up
folders=(
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
    "/scratch/bell/mstojano/d0outputs_new_07a"
)

HPSS_TARGET_DIR="/home/wxie/Milan/BELL_scratch"

echo "=== Starting HSI Archival with Checksum Verification ==="

for path in "${folders[@]}"; do
    if [ ! -d "$path" ]; then
        echo "WARNING: Local directory $path does not exist. Skipping."
        continue
    fi

    folder_name=$(basename "$path")
    parent_dir=$(dirname "$path")
    log_file="/home/wxie/out_$folder_name.log"

    echo "Archiving $folder_name to HPSS..."

    # 'put -c on -R' turns on checksum calculation on transfer
    cd "$parent_dir" && hsi "cd $HPSS_TARGET_DIR; put -c on -R $folder_name" &> "$log_file"
done

echo ""
echo "=== Starting Post-Transfer Verification ==="
echo "Folder Name | Local Files | HPSS Files | Integrity Check | Media Status"
echo "------------------------------------------------------------------------"

for path in "${folders[@]}"; do
    folder_name=$(basename "$path")
    
    if [ ! -d "$path" ]; then
        continue
    fi

    # 1. Count local files
    local_count=$(find "$path" -type f | wc -l)

    # 2. Query HPSS for remote file count and checksum verification
    # Run hashverify recursively to verify stored hashes
    hsi_verify_out=$(hsi "cd $HPSS_TARGET_DIR/$folder_name; hashverify -R ." 2>&1)
    
    # Get HPSS file count via ls
    hpss_count=$(hsi "cd $HPSS_TARGET_DIR/$folder_name; ls -1R" 2>/dev/null | grep -v '^/' | grep -v '^$' | wc -l)

    # Check media status (Disk cache vs Tape)
    tape_status=$(hsi "cd $HPSS_TARGET_DIR; ls -U $folder_name" 2>/dev/null | grep -i "TAPE" > /dev/null && echo "TAPE" || echo "DISK_CACHE")

    # Evaluate integrity status
    if echo "$hsi_verify_out" | grep -iq "error"; then
        check_status="FAILED (Checksum Error)"
    elif [ "$local_count" -ne "$hpss_count" ]; then
        check_status="FAILED (File Count Mismatch)"
    else
        check_status="PASSED"
    fi

    printf "%-25s | %-11d | %-10d | %-23s | %s\n" "$folder_name" "$local_count" "$hpss_count" "$check_status" "$tape_status"
done

echo "------------------------------------------------------------------------"
echo "Verification finished. Check individual log files in /home/wxie/out_*.log if any directory failed."
