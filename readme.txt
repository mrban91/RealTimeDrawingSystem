REAL TIME DRAWING SYSTEM

authors: nicolabresciani91@gmail.com
         daniele.marinelli91@gmail.com

PRE-REQUISITIES
- Windows OS in order to run the .exe file
- Be sure that the "palette.jpg" file is in the same folder of the .exe file
- Webcam connected to your PC. The webcam must be motionless
- Printed colour version of the sheet with crosses. The sheet must be motionless (we suggest to fasten the sheet with adhesive tape). 
  The webcam has to be focused on the sheet with all the crosses visible

HOW TO RUN THE SOFTWARE
- Execute the .exe file. 

HOW TO COMPILE THE CODE
The code has been developed with NetBeans IDE 8.0.2.
In order to compile the code you have to:
- Install the OpenCV libraries, v2.4.9 [http://opencv.org/downloads.html]
- Integrate the libraries with NetBeans [http://eyalarubas.com/opencv-installation-on-windows-netbeans-mingw.html]
- Install the Qt libraries v5.4 [https://www.qt.io/download/]
- Integrate the Qt libraries in NetBeans [http://wiki.netbeans.org/Talk:HowToSetup64-BitQt5WithNetBeans7.4OnWindows]
- Enable the "WITH_QT" field in CMake
- Right click on the project->Build->Qt->CustomDefinitions->Add->"LIBS +=C:/opencv/release/lib" [use your path]

FOLDER STRUCTURE
- /src contains the source file
- /doc contains the code documentation
- /bin contains the binary code with mandatory files for execution

BASIC INSTRUCTIONS
- Execute the .exe file.
- Use an illumination as stable and uniform as possible 
- Use the video preview to make sure that the sheet is fully focused
- Fix the webcam and paper 
- Before clicking "start drawing" make sure nothing covers the sheet
- After the calibration is performed use the addition windows to check if the parameters are set correctly:
    - if the application does not identify your hand lower the hand identification threshold
	- if the draw is too noisy increase the adaptive treshold shift or increase the size of the buffer
- If some artefacts appear use the clean draw function
- Use the save sketch button to save the draw
- If the saved draw still present some buttons apply the filter to it by clicking on filter application.