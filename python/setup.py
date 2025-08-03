from setuptools import setup, Extension
import pybind11
import os
import toml
import shutil
import glob

# Получаем абсолютный путь к корню проекта
project_root = os.path.abspath(os.path.join(os.path.dirname(__file__), '..'))

# Создаём папку include внутри пакета, если её нет
include_dir = os.path.join(os.path.dirname(__file__), 'ftservo', 'include')
os.makedirs(include_dir, exist_ok=True)

# Копируем все .hpp файлы из исходной папки include в папку пакета
src_include_dir = os.path.join(project_root, 'include')
for src in glob.glob(os.path.join(src_include_dir, '*.hpp')):
    dst = os.path.join(include_dir, os.path.basename(src))
    shutil.copy2(src, dst)

# Определяем расширение
ftservo_module = Extension(
    "ftservo.ftservo",
    sources=["ftservo/src/ftservo.cpp"],
    include_dirs=[
        pybind11.get_include(),
        os.path.join(os.path.dirname(__file__), 'ftservo', 'include')  # Используем локальную папку include
    ],
    library_dirs=["../build"],
    libraries=["FTServo_shared"],
    extra_compile_args=["-std=c++11"],
)

# Читаем метаданные из pyproject.toml
try:
    with open("pyproject.toml", "r") as f:
        pyproject_data = toml.load(f)
    project_meta = pyproject_data.get("project", {})
    authors = project_meta.get("authors", [])
    urls = project_meta.get("urls", {})

    author_name = authors[0].get("name") if authors and authors[0].get("name") else ""
    author_email = authors[0].get("email") if authors and authors[0].get("email") else ""
    homepage_url = urls.get("Homepage", "")

    # Пытаемся получить long_description из README.md, указанного в pyproject.toml
    readme_file = project_meta.get("readme")
    long_description = ""
    if readme_file and os.path.exists(readme_file):
        try:
            with open(readme_file, "r", encoding="utf-8") as f:
                long_description = f.read()
        except Exception:
            pass # Игнорируем ошибки чтения README

except Exception:
    # Если не удалось прочитать pyproject.toml, используем значения по умолчанию
    author_name = ""
    author_email = ""
    homepage_url = ""
    long_description = ""

# Настройка пакета
setup(
    ext_modules=[ftservo_module],
    packages=["ftservo", "ftservo.examples"],
    package_dir={"": "."},
    include_package_data=True,
    zip_safe=False,
    package_data={"ftservo": ["include/*.hpp"]},
    # Явно указываем метаданные для лучшей совместимости с инструментами типа pip show
    author=author_name,
    author_email=author_email,
    url=homepage_url,
    long_description=long_description,
    long_description_content_type="text/markdown",
    license="MIT",
)