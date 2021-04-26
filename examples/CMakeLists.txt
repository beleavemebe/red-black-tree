# Добавьте сюда исполняемые файлы с примерами работы со структурой данных
add_executable(examples examples.cpp)

target_link_libraries(examples PRIVATE project_paths project_warnings ${PROJECT_NAME})
