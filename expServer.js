const express = require('express')
const fileUpload = require('express-fileupload')
//const model = require('../Model/DetectAnomalies__')
const model = require('../Model/DetectAnomalies')
const fs=require('fs')
const path = require('path')

const app = express()
app.use(express.urlencoded({
    extended: false
}))
app.use(fileUpload())
app.use(express.static('../View'))

// when opening webbrowser with localhost:8080 it will open the view of the app with the form.
app.get("/", (req, res) => {
    res.sendFile("./index.html")
})

// when sending a POST with /detect it will
app.post("/detect", (req, res) => {
    let algorithm = req.body.algorithm
    if(req.files) {
        // get the files from the request
        let learn_file = req.files.learn_file
        let detect_file = req.files.detect_file

        // create files with the same content as the files given
        fs.writeFile('learn_file.csv', learn_file.data.toString(), function (err) {
            if (err) throw err;
          });
        var learn_file_path = '../../Controller/learn_file.csv'

        fs.writeFile('detect_file.csv', detect_file.data.toString(), function (err) {
            if (err) throw err;
          });
        var detect_file_path = '../../Controller/detect_file.csv'
        
        // send the model the pathes to the files
        let result = model.detect(algorithm, learn_file_path , detect_file_path)

        // delete the created files
        fs.unlink('./learn_file.csv', function (err) {
            if (err) throw err;
          });
        fs.unlink('./detect_file.csv', function (err) {
        if (err) throw err;
        });

        // write the result
        res.write(result)
    }
    res.end()
})
app.listen(8080, ()=>console.log("server started on port 8080"))