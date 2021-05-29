# Anomaly-Detection-WebApp
The web app we present using the REST principles, allows the user to get service from the server and load two files;
The first file is a file from which the model is leraning the normal behavior, and the second is a file that the user want to investigate the anomalies.

There are two ways our web app can service a user.
The first is from HTML page, in which the user choose the algorithm of detection, and load the files.
When press the botton, the anomalies will appear in an inner frame and the user will be able to read it.
The second is from a POST request that include the algorithm and the files and the user will get the anomalies in a JSON from the server.

Both ways using HTML RESTful requests with MVC architecture.

# Folders and Files
In the GIT folder of the Anomaly-Detection-WebApp project there is the main branch with the lastest changes, a folder with PDFs explanations about the main classes and of course a folder named "ADP2-Flight Inspection App" with all the project files. 
Our project is devided to 3 main folders:

Model - the code that response to detect the anomalies from the given files 

Controller - the code that response on getting the information from the user, send it to the model, get the result from the model and send the result to the user 

View - the code that response to the view the user see and use. In this case, the HTML pages.


# Prerequests
In oreder to use our web app, you will need to use node.js.

**Installing node.js:**

The official Node.js website has installation instructions for Node.js: https://nodejs.org

In oreder to use the C code alogoritms in the app you will need to follow below instructions:

**Addon:**

# First running

**Open the server:**

In the command line, from the the address of the Controller folder, you will need to use the command: "node expServer.js".
This will open the server and will make it listen to port 8080 on your localhost device.
After running this command you will be able to open the browser in the address "localhost:8080/"
and get the HTML page, or altrenative to use the address "localhost:8080/detect/" with the algoritm and files you want to load and get back the JSON of the anomalies.
If you want to shut the server, you can use ctrl+c and press Y.

# Links to the full project's explenation in git

# link to the video



