# Running the C Program

## Prerequisites
Make sure you have `make` and a C compiler (such as `gcc`) installed on your system.

## Steps to Compile and Run

1. Navigate to the source code directory:
   ```sh
   cd Lab_2_Source_Code
   ```

2. Compile the program using `make`:
   ```sh
   make
   ```

3. Run the program using the following format:
   ```sh
   ./sim <num_packets> <packet_loss_prob> <packet_corruption_prob> <packet_interval> <trace_level>
   ```

## Cleaning Up
To remove compiled files, you can run:
```sh
make clean
```

