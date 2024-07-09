import os

def replace_hash_in_filenames(directory):
    for root, dirs, files in os.walk(directory):
        for filename in files:
            if " #" in filename:
                new_filename = filename.replace(" #", "-")
                old_filepath = os.path.join(root, filename)
                new_filepath = os.path.join(root, new_filename)
                os.rename(old_filepath, new_filepath)
                print(f'Renamed: {old_filepath} -> {new_filepath}')

replace_hash_in_filenames(".")
