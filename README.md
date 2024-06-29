# CameraControlBT-TDS3P for Canon digital cameras with Bluetooth connectivity based to LILIGO® T-Display S3 Pro

- Bluetooth is fully functional except for Wide and Tele Buttons. I've no Camera to check it.

# Hardware

- [LILIGO® T-Display S3 Pro](https://www.lilygo.cc/products/t-display-s3-pro)

# Build environment

- [PlatformIO](https://platformio.org/)
  - [Choosing PlatformIO IDE for VSCode](https://platformio.org/install/ide?install=vscode)
- [Visual Studio Code](https://code.visualstudio.com/)
- [SquareLine Studio](https://squareline.io/) - UI Design

# Screeshots

## Start screen

![start](docs/start.png)

## Settings screen

![settings](docs/settings.png)

## Bluetooth remote control screen

![remote](docs/remote.png)

## Intervalometer

![interval](docs/interval.png)

- #P : number of pictures to take

- IvT : Interval time between shots

- XpT : Exposure time, if XpT > IvT then IvT is set to 0s. Setting the Exposure time only makes sense in *BULB* mode. Minimum time between shots is 4s.
