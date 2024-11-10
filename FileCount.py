import os

numbers_list = [
    13, 7, 12, 10, 11, 8, 4, 7, 6, 8, 7, 6, 11, 8, 9, 11, 0, 1, 5, 5, 7, 8, 
    16, 6, 5, 9, 7, 3, 6, 5, 16, 7, 5, 9, 7, 4, 6, 4, 9, 6, 5, 3, 5, 8, 8, 6, 
    10, 5, 6, 8, 4, 11, 5, 5, 11, 7, 8
]

def count_files_in_step_dirs():
    with open("count.txt", "w") as f:
        total_count = 0
        for item in sorted(os.listdir('.')):
            if not(os.path.isdir(item) and item.startswith("step")): continue
            num = int(item.split(" ")[1])
            if (num == 17 or num == 18):
                f.write("\n")
                continue
            file_count = len([file for file in os.listdir(item) if os.path.isfile(os.path.join(item, file)) and file.endswith(".c")])
            f.write(f"{item} : {file_count} / {numbers_list[num-1]}\n")
            total_count += file_count
        f.write(f"\n총 파일 수: {total_count}\n")

count_files_in_step_dirs()