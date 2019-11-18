# OpenGL Demos

This repository contains a compendium of small OpenGL applications built to demonstrate concepts of Computer Graphics. It is used as support material for the Computer Graphics course at the [Federal University of Fronteira Sul](https://www.uffs.edu.br). The demos in this repository were mainly created by [Cesar Tadeu Pozzer](http://www-usr.inf.ufsm.br/~pozzer/) at the [Federal University of Santa Maria](https://www.ufsm.br).

> **Course responsible:** Fernando Bevilacqua [fernando.bevilacqua@uffs.edu.br]

## Getting started

All demos should work fine on Windows and Linux. Follow the guides below according to the platform you are using.

### 1. Windows
#### 1.1 Prerequisites

Ensure that your machine has up-to-date graphic drivers and a development environment is installed, e.g. [Visual Studio Community](https://visualstudio.microsoft.com/). You also need [git](https://gitforwindows.org/) installed.

#### 1.2 Clone the project

Clone this repository in a folder of your choice, e.g. `c:\`:

```
git clone https://github.com/Dovyski/opengl-demos.git opengl-demos && cd opengl-demos
```
#### 1.3 Open the solution file

Open the solution file named `OpenGL-demos.sln` to load all the demos/projects.

#### 1.4 Build all demos (optional)

If you want to test all demos/projetcs right away, after opening the solution file, go to `Build -> Build Solution` (or press <kbd>F7</kbd>). If nothing goes wrong, you should see several executable files in the folder `build\x64\Debug` (or `build\x64\Release` if you compiled using the release configuration)

#### 1.5 Running and compiling a particular demo

You can compile and run any of the demos/projects individually by right-clicking it in the solution explorer, then selecting `Set as Startup Project`. After that, hit <kbd>F5</kbd> and the project will compile and run.

### 2. Linux

#### 2.1 Prerequisites

Ensure that your machine has up-to-date graphic drivers and a development environment is installed, e.g. `build-essential` is installed. If you are not sure you have a dev environment setup, run:

```
sudo apt update && sudo apt install build-essential git
```

#### 2.2 Clone the project

Clone this repository in a folder of your choice, e.g. `/tmp`:

```
git clone https://github.com/Dovyski/opengl-demos.git opengl-demos && cd opengl-demos
```

#### 2.3 Install project dependencies

The demos use several 3rd-party libraries that must be installed. You can install them all by running the following command in the project root folder (the one containing the `Makefile` and `OpenGL-demos.sln` files):

```
make install-deps
```

The command will ask for a sudo password and proceed with the installation of all dependencies.

#### 2.4 Build all demos (optional)

If you want to test all demos/projetcs right away, you can use `make` to build them at once. In the project root folder, run:

```
make all
```

#### 2.5 Running and compiling a particular demo

You can compile and run any of the demos/projects individually by running the command `make <demo-name>` where `<demo-name>` is the name of a demo. For example, to compile the demo `rotating-cube`, run:

```
make rotating-cube
```

If you want to list the name of all available demos or get help about the build process, run:

```
make help
```

You can also compile a particular demo by navigating into its source code folder and running `make` there:

```
cd src/rotating-cude && make
```

### 3. Demos related to `Three.js` (optional)

There are several demos that use [Three.js](https://threejs.org), a lightweight cross-browser JavaScript library/API used to create and display animated 3D computer graphics on a Web browser.

To improve your experience with the demos related to `Three.js`, install [Visual Studio Code](https://code.visualstudio.com):

```
apt install code
```

Then install the [Live Server](https://marketplace.visualstudio.com/items?itemName=ritwickdey.LiveServer) extension:

```
code --install-extension ritwickdey.liveserver
```

Finally, open the `opengl-demos` folder in Visual Studio Code and click the `Go Live` button in the taskbar:

![Gif showing how the Go Live button in the taskbar](.github/docs/vscode-live-server-animated-demo.gif)

Demos related to three.js will be available under `/src/threejs-*/`, e.g. [http://127.0.0.1:5500/src/threejs-hello-world/](http://127.0.0.1:5500/src/threejs-hello-world/).

## License

The code files in this repository have mixed licenses. Please refer to each file/project to check its license.

## Changelog

See all changes in the [CHANGELOG](CHANGELOG.md) file.

## Useful links

* [opengl-tutorial.org](http://www.opengl-tutorial.org/)
* [Modern OpenGL Tutorials](http://ogldev.atspace.co.uk/)