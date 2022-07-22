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

------------------

#### When Using Visual Studio:

**The required C++ standard is C++ 20**, so make sure you have at least **MSVC 19.28**. If you're not using Visual Studio, make sure you have compilers which support C++ 20.

When using CMake, make sure to choose Native compilers, and x64 configuration. Then just open {dir. where I cloned}/Symplektis/build/Symplektis_ConsoleApp.sln or click **Open Project** in CMake GUI.

**Known CMake Problem**: After first clone, you may need to **configure and generate twice**, otherewise all the ~900 subprojects of Eigen an Boost get loaded into the VS solution.

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

## Architecture Components & Their Purpose:

![SymplektisBaseArchitecture](https://github.com/MCInversion/Symplektis/blob/main/InfoImages/Symplekt_Architecture.png)

Symplektis is meant to serve as the foundation for a "`Symplekt_App`" which introduces new functionality by combining functionalities in the `Kernel` block. The `Kernel` uses base functionality in the `Basis` block, and finally there's the `External` block which hosts all thrid-party libraries such as GoogleTest and Eigen.

### [] **Symplekt_App**

It can be a simple demo executable or a more complex project with multiple helper classes and/or utilities. This component will, most of the time, consist of only a single `main()` function with some helper utilites. The true extent of this item is still unknown at this point and will be better known after apps like ShrinkWrapper.exe will be implemented. The ShrinkWrapper app will, for example, use all Kernel components to:
 - save/load standardized mesh/implicit geometries to/from selected directories,
 - perform time and memory-consumption measurements for the algorithms,
 - voxelize & construct SDFs of imported mesh geometries,
 - use surface fairing and decimation methods to "shrink-wrap" target meshes with a chosen starting surface,
 - perform analysis operations on mesh and volumetric data within the app or from loaded files.
 - print additional reports about the above functionality, some of them integrated as inputs for other tools e.g. Wolfram Mathematica, (PlantUML)[https://www.planttext.com/].
 
This means that Symplektis ShrinkWrapper will need to accumulate the above functionality first in a single `main()` where flags would be turned on/off to run different settings, then a command line interface will be implemented for the Symplekt_IOService component which will parse `argv**` into Symplektis commands, and finally a user interface incorporating all of the above (including a command line option) will be implemented.

------------------

### [] **Kernel**:

Symplektis Kernel is meant to contain all functionality available to the user, essentially serving as an API for Symplekt_App. At this point, there is no reason for other components to be available to the Symplekt_App. All of the operations an app could perform will be interfaced and/or implemented in this block. That entails I/O operations, fundamental geometric functionality, and the key algorithms used in the app.

#### -> **Symplekt_IOService**:
Input/Output service. Deals with import/export of 3D data (image or polygonal), analysis & timing reports, and console output.

#### -> **Symplekt_Algorithms**: 

Initially there were two components, namely for "analysis" and "processing" subroutines.

An "analysis subroutine" is any algorithm performed on mesh or implicit geometry data which outputs a scalar, vector, or tensor field defined either on the geometry itself, or on the ambient (Euclidean) space of the evaluated geometry.

A "processing subroutine" is any algorithm performed on mesh or implicit geometry data which outputs a modified (processed) geometry of the same type. For example, remeshing, decimation, triangulation, smoothing, or fairing tools.

At this stage, however, it seems illogical to separate them into two components which might potentially overlap quite a lot. In particular, `AABBTree` might be used to "analyze" a mesh by computing a distance to it, or for "processing" it before a shrink-wrapper tool is used.

#### -> **Symplekt_GeometryKernel**:

Implements higher-level math primitives, such as `Vector3`, `Quaternion`, `Matrix4` etc. including basic mathematical and geometry utils such as: triangle-box intersection, triangulation etc, and geometric representations (e.g. mesh, implicit) of 3D objects.

------------------

### [] **Basis**:

This block forms the "basis" for the Kernel block, that is: a low-level support for IOService, Algorithms and GeometryKernel. Components in this block contain abstract representations of items in the Kernel block as well as data representations for various purposes, including those for numerical methods invoking Eigen functionality.

#### -> **Symplekt_UtilityGeneral**:
A low-level component containing base error handlers, assertions, timing etc.

#### -> **Symplekt_DataReps**:
A low-level component with useful data structure implementations (e.g.: binary tree).

#### -> **Symplekt_Numerics**:
A low-level processing component delegated to by mid-level analysis and processing components to perform large-scale numerical computations (e.g.: linear solvers, diagonalization, ...). Uses the [Eigen library](https://gitlab.com/libeigen/eigen).

------------------

### [] Third-Party (External):

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
