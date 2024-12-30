cmake_minimum_required(VERSION 3.10)
project(MyProject)

# ソースファイル
set(SOURCES main.cpp)

# 実行ファイルの名前を設定
add_executable(weilang ${SOURCES})

# 出力ディレクトリをカスタマイズ
set_target_properties(weilang PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
