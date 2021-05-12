const express = require('express')
const fileUpload = require('express-fileupload')
//const model = require('../Model/DetectAnomalies__')
const model = require('../Model/DetectAnomalies')

const app = express()
app.use(express.urlencoded({
    extended: false
}))
app.use(fileUpload())
app.use(express.static('../View'))


// when opening webbrowser with localhost:8080 it will open the view of the app with the form.
app.get("/", (req, res) => {
    //res.sendFile("./noa.html")
    res.sendFile("../View/public/noa.html")
    console.log("noa")
})

// app.get("/result", (req, res) => {
//     res.sendFile("./resultView.html")
// })


// when sending a POST with /detect it will get the result from the model and send it back to the view.
app.post("/detect", (req, res) => {

    let algorithm = req.body.algorithm
    if(req.files) {
        // get the files from the request
        let learn_file = req.files.learn_file
        let detect_file = req.files.detect_file
        
        // send the model the pathes to the files
        let result = model.detect(algorithm, learn_file.data.toString() , detect_file.data.toString())
        req.anomalies = result
        
        //res.redirect('/result')
        //res.render('resultView.html')
        // if a callback is specified, the rendered HTML string has to be sent explicitly
        app.use(express.static('../View'))
        res.sendFile('./resultView.html')
        // write the result
        //res.write(req.anomalies)
    }
    res.end()
})
app.listen(8080, ()=>console.log("server started on port 8080"))