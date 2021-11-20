var express = require('express');
var fileSaver = require('../models/receive/fileSaver.js');
var runCompiler = require('../models/receive/runCompiler.js')
var router = express.Router();



/* GET home page. */
router.get('/',function(req, res, next){
    res.render('index',{title: 'Express'});
});

router.post('/',function(req, res, next){
    // console.log("start save");
    // fileSaver.save(req.body.code, 'code.source', );
    // console.log("end save");
    var myPromise = new Promise(function(resolve,reject){
        fileSaver.save(req.body.code, 'code.source', );
        console.log("end save");
        resolve("start run")
    });

    myPromise.then(function(successMessage){
        console.log(successMessage);
        runCompiler.run("main.exe");
        resolve("end run");
        
    });
    res.render('receive');
    // console.log("start exe");
    // runCompiler.run("main.exe");
    // console.log("end exe");

    
});



module.exports = router;