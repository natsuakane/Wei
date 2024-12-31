# 必要なCMakeのバージョン
cmake_minimum_required(VERSION 3.10)

# プロジェクト名とC++標準
project(Wei-lang)
set(CMAKE_CXX_STANDARD 17)

# ソースディレクトリの設定
set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

# ヘッダーファイルのディレクトリをインクルードパスに追加
include_directories(${INCLUDE_DIR})

# ソースファイルの設定
file(GLOB_RECURSE SOURCES ${SOURCE_DIR}/*.cpp)

# 実行ファイルの生成
add_executable(weilang ${SOURCES})
