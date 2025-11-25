import os

# Configuration
input_folder = ".\\Transport"  # <-- change this to your folder
output_file = "combined.txt"           # <-- name of the big file

# Get all files in the folder
files = [f for f in os.listdir(input_folder) if os.path.isfile(os.path.join(input_folder, f))]

with open(output_file, "w", encoding="utf-8") as outfile:
    for filename in files:
        file_path = os.path.join(input_folder, filename)
        with open(file_path, "r", encoding="utf-8") as infile:
            outfile.write(f"\n\n--- {filename} ---\n\n")  # optional: separate files
            outfile.write(infile.read())

print(f"All files combined into {output_file}")
