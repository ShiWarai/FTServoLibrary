from setuptools import setup, Extension
import pybind11
import os
import toml # Import the toml library

# Define the extension
ftservo_module = Extension(
    "ftservo.ftservo",
    sources=["ftservo/src/ftservo.cpp"],
    include_dirs=[
        pybind11.get_include(),
        "/home/orangepi/rtulab_feetech/library/FTServoLibrary/include"  # Absolute path for reliability
    ],
    library_dirs=["../build"],
    libraries=["FTServo_shared"], # Link against the shared library built by CMake
    extra_compile_args=["-std=c++11"],
    #runtime_library_dirs=["$ORIGIN"], # May need adjustment depending on deployment
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
    packages=["ftservo", "ftservo.examples"], # Ensure examples directory is included
    package_dir={"": "."},
    include_package_data=True, # Necessary to include files specified in pyproject.toml package-data
    zip_safe=False, # Usually required for extensions

    # Explicitly set metadata for better compatibility with tools like pip show
    author=author_name,
    author_email=author_email,
    url=homepage_url,
    long_description=long_description,
    long_description_content_type="text/markdown", # Assuming README is markdown
    license="MIT", # Explicitly set license for pip show

    # Other metadata like name, version, description, requires-python, dependencies, etc.
    # are typically read by setuptools directly from pyproject.toml (PEP 621) if not specified here.
    # Explicitly adding them here would duplicate, but might be necessary if PEP 621 reading is inconsistent.
    # Let's test without explicit duplication first.
)