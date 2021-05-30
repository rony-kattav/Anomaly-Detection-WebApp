# Anomaly-Detection-WebApp
The web app we present using the REST principles, allows the user to get service from the server and load two files;
The first file is a file from which the model is leraning the normal behavior, and the second is a file that the user want to investigate the anomalies.

There are two ways our web app can service a user.
The first is from HTML page, in which the user choose the algorithm of detection, and load the files.
When pressing the botton, the anomalies will appear in an inner frame and the user will be able to read it.
The second is from a POST request that includes the algorithm and the files. The user will get the anomalies in a JSON from the server.

Both ways using HTML RESTful requests with MVC architecture.

# Folders and Files
In the GIT folder of the Anomaly-Detection-WebApp project there is the main branch with the lastest changes, a folder with PDFs explanations about the main classes and a folder named "ADP2-Flight Inspection App" with all the project files. 
Our project is devided to 3 main folders:

Model - the code that responsible to detect the anomalies from the given files.

Controller - the code that responsible on getting the information from the user, send it to the model, get the result from the model and send the result to the user.

View - the code that responsible to the view the user see and use. In this case, the HTML pages.


# Prerequests
In oreder to use our web app, you will need to use node.js.

**Installing node.js:**

The official Node.js website has installation instructions for Node.js: https://nodejs.org
Then, you should go to your CLI (in windows-cmd) and both inside the **Controller** and inside the **Model** directories make the command **npm i** so it will download the required node-modules.


# First running

**Open the server:**
In the command line, from the the address of the Controller folder, you will need to use the command: **node expServer.js**.
This will open the server and will make it listen to port 8080 on your localhost device.

**Using the app via HTML:**
After running this command you will be able to open the browser in the address "localhost:8080" and get the HTML page. There you will follow the instructions and after that it will display for you the anomalies report.
If you want to shut down the server, you can use ctrl+c and press Y.

**Using the app via code:**
After running "node expServer.js" command, use the address "localhost:8080/detect/" and send the detecting algoritm ("Hybrid"/"Reggression") and the csv files as shown in the video bellow. then you will get back the JSON of the anomalies.

# Link to UML of the project
https://github.com/rony-kattav/Anomaly-Detection-WebApp/blob/main/Anomaly_Detection_WebApp_UML.pdf

# link to the video
https://youtu.be/3-FDk_oGhQY


