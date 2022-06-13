<p align="center">
  <img width="500" height="350" src="https://github.com/MCInversion/Symplektis/blob/main/InfoImages/SymplektLogo.jpg">
</p>

### What is Symplektis?

The name "Symplektis" is a derivation of term "simplex", which is the fundamental building block in mesh geometry, for example a 0-simplex is a point, a 1-simplex is a line segment, 2-simplex a triangle and 3-simplex a tetrahedron. You can use these objects to construct a shape and do all kinds of operations on it, as if it were from a real material.

> The concept of a simplex was known to William Kingdon Clifford, who wrote about these shapes in 1886 but called them "prime confines". Henri Poincaré, writing about algebraic topology in 1900, called them "generalized tetrahedra". In 1902 Pieter Hendrik Schoute described the concept first with the Latin superlative simplicissimum ("simplest") and then with the same Latin adjective in the normal form simplex ("simple").
>> https://en.wikipedia.org/wiki/Simplex

The purpose of the library is to utilize mesh processing and 3D representation algorithms and utilities intended for academic purposes. The core philosophy is to analyze 3D shapes and process them given a set of criteria. Most importantly, it is to be maintainable and expandable. Hence, Symplektis should gather algorithms and approaches from many research projects to come.

At this point, Symplektis is a console app. In the following versions, we will add a command line interface. And later still, we consider adding a GUI. 

------------------

### License

Symplektis is provided under [MIT license](https://github.com/MCInversion/Symplektis/blob/main/LICENSE). 

Copyright (c) 2021-2022 Martin Cavarga, 
Department of Algebra and Geometry, 
Faculty of Mathematics Physics and Informatics, Commenius University 
<martin.cavarga@fmph.uniba.sk, mcavarga@gmail.com>.


------------------

### How to Use Symplektis?

You need [git](https://github.com/git-guides/install-git), of course. And then you need [CMake](https://cmake.org/) of version at least 3.14.

Clone the repository (recursively to also clone "External" submodules):

```sh
git clone https://github.com/MCInversion/Symplektis.git
```

Do not use `clone --recursive` external dependencies in `./External` folder will be cloned by CMake.

**Configure** and **Generate** project files (using [CMake](https://cmake.org/) from command line):

```sh
cd Symplektis && mkdir build && cd build && cmake .. && make
```

or **Configure** and **Generate** using CMake GUI:

![CMakeGUISetup](https://github.com/MCInversion/Symplektis/blob/main/InfoImages/ImgCmakeGUI.jpg)

**Disclaimer**: At this point, you need to **Generate** one more time otherwise the CMake will also load all (~900) Eigen (sub)projects.

------------------

#### When Using Visual Studio:

**The required C++ standard is C++ 20**, so make sure you have at least **MSVC 19.28**. If you're not using Visual Studio, make sure you have compilers which support C++ 20.

When using CMake, make sure to choose Native compilers, and x64 configuration. Then just open {dir. where I cloned}/Symplektis/build/Symplektis_ConsoleApp.sln or click **Open Project** in CMake GUI.

Build all Symplektis projects either from Solution Explorer, or just run using Local Windows Debugger (F5).

Also, set **Symplektis_ConsoleApp** as a startup project (right-click in Solution Explorer) to make sure the correct executable is run during Debug or Release configuration. Other executables can be added in the topmost CMakeLists.txt.

------------------

#### Unit Testing with GoogleTest in Visual Studio:

When developing new functionalities, or modifying the existing ones, it is essential to properly test the outputs of individual components (methods, functions). For this purpose, we use the [Google Test C++ testing framework](https://google.github.io/googletest/) which is cloned as a submodule in Symplektis/External/GoogleTest, and installed with CMake. 

The test suites (for example `GeometryBase_TestSuite` which tests the functionality of `Symplekt_GeometryBase` library) have their own executables. They can be run in Visual Studio via the *Test Explorer*:

![VSTestExplorer](https://github.com/MCInversion/Symplektis/blob/main/InfoImages/VSTestExplorer.png)

or, if you have the ["Test Adapter for Google Test" Visual Studio component](https://docs.microsoft.com/en-us/visualstudio/test/how-to-use-google-test-for-cpp?view=vs-2019) installed, you can run or debug tests by right-clicking a project with tests in the Solution Explorer:

![VSTestAdapter](https://github.com/MCInversion/Symplektis/blob/main/InfoImages/VSGTestAddin.png)

If you want to add a new suite to a component, just add a \*.cpp file where you want your tests. CMake will automatically map it into the test suite executable, for example `ProcessingKernel_TestSuite`. Just make sure you follow the [Google Test syntax for test cases and suites](https://google.github.io/googletest/primer.html).

Among the useful guidelines, we follow the [Arrange-Act-Assert pattern](https://automationpanda.com/2020/07/07/arrange-act-assert-a-pattern-for-writing-good-tests/):

```
TEST(OBJImport_TestSuite, SFBunnyOBJFile_Import_ImportedSFBunnyData)
{
	// Arrange
	const auto fileFullPath = symplektRootPath / "Symplekt_ResourceData\\" / "bunnySimple.obj";

	// Act
	const auto importStatus = OBJImporter::Import(fileFullPath);
	const auto& geomData = OBJImporter::Data();

	// Assert
	EXPECT_EQ(importStatus, ImportStatus::Complete);
	EXPECT_EQ(geomData.Name, L"bunnySimple");
	EXPECT_EQ(geomData.Vertices.size(), 2503);
	EXPECT_EQ(geomData.VertexIndices.size(), 4968);
	EXPECT_EQ(geomData.VertexNormals.size(), 0);
}
```

------------------

### Architecture Components & Their Purpose:

![SymplektisBaseArchitecture](https://github.com/MCInversion/Symplektis/blob/main/InfoImages/Symplekt_Architecture.png)

#### -> **Symplekt_UtilityGeneral**:
A low-level component containing base error handlers, assertions, timing etc.

#### -> **Symplekt_DataReps**:
A mid-level component with useful data structure implementations (e.g.: binary tree).

#### -> **Symplekt_GeometryBase**:
A mid-level geometry component containing all building blocks of geometric objects and transformations, such as: `Vector3`, `Quaternion`, `Matrix4` etc. including basic mathematical and geometry utils such as: triangle-box intersection etc.

#### -> **Symplekt_GeometryReps**:
A mid-level geometry component responsible for geometric representations (e.g. mesh, implicit) of 3D objects.

#### -> **Symplekt_IOService**:
Input/Output service. Deals with import/export of 3D data (image or polygonal), analysis & timing reports, and console output.

#### -> **Symplekt_Numerics**:
A low-level processing component delegated to by mid-level analysis and processing components to perform large-scale numerical computations (e.g.: linear solvers, diagonalization, ...). Uses the [Eigen library](https://gitlab.com/libeigen/eigen).

#### -> **Symplekt_AnalysisKernel**:

An "analysis subroutine" is any algorithm performed on mesh or implicit geometry data which outputs a scalar, vector, or tensor field defined either on the geometry itself, or on the ambient (Euclidean) space of the evaluated geometry.

#### -> **Symplekt_ProcessingKernel**:

A "processing subroutine" is any algorithm performed on mesh or implicit geometry data which outputs a modified (processed) geometry of the same type. For example, remeshing, decimation, triangulation, smoothing, or fairing tools.

------------------

### Third-Party (External):

#### -> **GoogleTest**:

GoogleTest is Google’s C++ testing and mocking framework. We include it to individual components of Symplektis.

Repo: https://github.com/google/googletest

#### -> **Eigen**:

Eigen is a C++ template library for linear algebra: matrices, vectors, numerical solvers, and related algorithms. We use it primarly in the Symplekt_AnalysisKernel and Symplekt_ProcessingKernel components.

Repo: https://gitlab.com/libeigen/eigen

#### -> **Poly2Tri**:

Poly2Tri is a small C++ library for triangulating polygonal contours using constrained Delaunay triangulation (CDT). Since it was necessary to do multiple adjustments to the library, we embedded it in Symplekt_GeometryBase rather than include it as an external dependency.

\[Domiter V. and Zalik B. (2008) Sweep‐line algorithm for constrained Delaunay triangulation\] 

Repo: https://github.com/jhasse/poly2tri
