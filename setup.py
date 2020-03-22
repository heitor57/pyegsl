from distutils.core import setup, Extension

def main():
    setup(name="pyegsl",
          version="1.0.0",
          description="Python easy interface to gsl with some friendly interfaces",
          author="Heitor L. Werneck",
          author_email="heitorwerneck@hotmail.com",
          url = 'https://github.com/heitor57/pyegsl'
          license="MIT",
          ext_modules=[Extension(
              "binomial", ["src/binomial.cpp"],
              libraries = ['gsl','gslcblas'])])

if __name__ == "__main__":
    main()

