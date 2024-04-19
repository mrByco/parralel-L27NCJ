#!/bin/bash

img_sizes=(512 1024 2048 4096)
radiusses=(2 5 10 20)
num_of_measurings=1
threads_for_cpu=10

run_files=("./run_open_cl.sh" "./run_open_mp.sh")

output_file="experiment_results.csv"
echo "Script,Image Size,Radius,Mean Time" > "$output_file"

perform_experiment() {
    local file=$1
    local size=$2
    local radius=$3
    local total_time=0
    local count=0

    for (( i=1; i<=num_of_measurings; i++ )); do
        # Execute the script and capture the output
        local time=$(bash "$file" $size $radius $threads_for_cpu)
        if ! [[ "$time" =~ ^[0-9]+([.][0-9]+)?$ ]]; then
            echo "Error: Invalid time value received ('$time')"
            return 1
        fi
        total_time=$(echo "$total_time + $time" | bc)
        ((count++))
    done

    local mean=$(echo "scale=2; $total_time / $count" | bc)
    echo "$file,$size,$radius,$mean" >> "$output_file"
}

for file in "${run_files[@]}"; do
    for size in "${img_sizes[@]}"; do
        for radius in "${radiusses[@]}"; do
            perform_experiment "$file" $size $radius
        done
    done
done

echo "Experiments completed. Results saved to $output_file."
