from glob import glob
import re

if __name__ == "__main__":
    file_path = "test_files"
    files = glob(f"{file_path}/*.npz")
    numbers = [int(re.search("(\d+)", f).groups()[0]) for f in files]
    next_index = max(numbers) + 1
    print(f"Next index: {next_index}")
    
