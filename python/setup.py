from setuptools import setup, Extension
import pybind11
import os
import toml
import shutil

# Get the absolute path to the project root directory
project_root = os.path.abspath(os.path.join(os.path.dirname(__file__), '..'))

# Create include directory in the package if it doesn't exist
include_dir = os.path.join(os.path.dirname(__file__), 'ftservo', 'include')
os.makedirs(include_dir, exist_ok=True)

# Copy header files to the package
header_files = [
    'SCSerial.hpp',
    'SCSCL.hpp',
    'SCS.hpp',
    'INST.hpp',
    'HLSCL.hpp',
    'SCServo.hpp',
    'SMSBL.hpp',
    'SMSCL.hpp',
    'SMS_STS.hpp'
]

for header in header_files:
    src = os.path.join(project_root, 'include', header)
    dst = os.path.join(include_dir, header)
    if os.path.exists(src):
        shutil.copy2(src, dst)

# Define the extension
ftservo_module = Extension(
    "ftservo.ftservo",
    sources=["ftservo/src/ftservo.cpp"],
    include_dirs=[
        pybind11.get_include(),
        os.path.join(os.path.dirname(__file__), 'ftservo', 'include')  # Use local include directory
    ],
    library_dirs=["../build"],
    libraries=["FTServo_shared"],
    extra_compile_args=["-std=c++11"],
)

# Read metadata from pyproject.toml
try:
    with open("pyproject.toml", "r") as f:
        pyproject_data = toml.load(f)
    project_meta = pyproject_data.get("project", {})
    authors = project_meta.get("authors", [])
    urls = project_meta.get("urls", {})

    author_name = authors[0].get("name") if authors and authors[0].get("name") else ""
    author_email = authors[0].get("email") if authors and authors[0].get("email") else ""
    homepage_url = urls.get("Homepage", "")

    # Attempt to get long_description from README.md specified in pyproject.toml
    readme_file = project_meta.get("readme")
    long_description = ""
    if readme_file and os.path.exists(readme_file):
        try:
            with open(readme_file, "r", encoding="utf-8") as f:
                long_description = f.read()
        except Exception:
            pass # Ignore errors reading README

except Exception:
    # Provide default/empty metadata if pyproject.toml cannot be read
    author_name = ""
    author_email = ""
    homepage_url = ""
    long_description = ""

# Package setup
setup(
    ext_modules=[ftservo_module],
    packages=["ftservo", "ftservo.examples"],
    package_dir={"": "."},
    include_package_data=True,
    zip_safe=False,

    # Explicitly set metadata for better compatibility with tools like pip show
    author=author_name,
    author_email=author_email,
    url=homepage_url,
    long_description=long_description,
    long_description_content_type="text/markdown",
    license="MIT",
)