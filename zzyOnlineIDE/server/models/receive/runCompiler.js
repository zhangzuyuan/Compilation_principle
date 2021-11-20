var fs = require('fs');
var exec = require('child_process').execFile;

var runCompiler = function(fileName){
    console.log("hello exe");
    var fPath = './public/compiler/out/'
    exec(`${fPath}${fileName}`,function(err, data) {
        console.log(data);
    });
};


exports.run = runCompiler;