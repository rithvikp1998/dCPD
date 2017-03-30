# dCPD
This is a basic Common Printing Dialog built using Qt framework. This is being built as part of GSoC '17 preparation. The screenshot of the dialog is attached. Note that the screenshot changes as the project progresses.

To run the app, download ``` standalone.AppImage ``` (This appimage packs all the required libraries into one single file thus eliminating the need for different users install required Qt packages in their PCs). Also download ``` test.pdf ``` and copy it to ``` /tmp/ ``` directory because ``` poppler-qt5 crashes ``` if the file is not present(Issue to be fixed). Once the pdf is copied and appimage downloaded, simple cd into the corresponding directory and execute it using ``` ./standalone.AppImage ```

To build from source code, ``` cd ``` into the source code directory and execute the following commands:
```
mkdir build; cd build
qmake ../dCPD.pro
make
cp ../test.pdf /tmp/
./dCPD
```

Please note that for the build to work, you need to have Qt 5.8 installed. It is released by Qt but not present in Ubuntu's package repository, so you have to download and install it from Qt's website here: https://www.qt.io/download-open-source/

![Alt text](Images/screenshot.png?raw=true)

UPDATE: Mar 28, 2017

![Alt text](Images/screenshot2.png?raw=true)

UPDATE 2: Mar 28, 2017

![Alt text](Images/screenshot3.png?raw=true)
