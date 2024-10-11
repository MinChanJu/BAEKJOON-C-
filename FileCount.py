import os
import pandas as pd

numbers_list = [
    13, 7, 12, 10, 11, 8, 4, 7, 6, 8, 7, 6, 11, 8, 9, 11, 0, 1, 5, 5, 7, 8, 
    16, 6, 5, 9, 7, 3, 6, 5, 16, 7, 5, 9, 7, 4, 6, 4, 9, 6, 5, 3, 5, 8, 8, 6, 
    10, 5, 6, 8, 4, 11, 5, 5, 11, 7, 8
]


def count_files_in_directories(base_dir='.'):
    # 결과를 저장할 리스트
    data = []
    
    # 현재 디렉토리의 서브 디렉토리들을 가져옴
    for root, dirs, files in os.walk(base_dir):
        for index, dir_name in enumerate(dirs):
            dir_path = os.path.join(root, dir_name)
            file_count = len([f for f in os.listdir(dir_path) if os.path.isfile(os.path.join(dir_path, f))])
            file_count //= 2
            # 디렉토리와 파일 개수를 리스트에 추가
            data.append({'Directory': dir_name, 'File Count': file_count, 'Total Number': numbers_list[index], 'Not Solve': numbers_list[index]-file_count})
    
    # 데이터프레임으로 변환
    df = pd.DataFrame(data)
    
    # 엑셀 파일로 저장
    output_file = 'file_counts.xlsx'
    df.to_excel(output_file, index=False)
    print(f"Data saved to {output_file}")

# 실행
count_files_in_directories()
