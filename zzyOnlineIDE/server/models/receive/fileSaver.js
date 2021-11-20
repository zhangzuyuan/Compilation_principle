var fs = require('fs');

var fileSave = function(data,fileName){
    var fPath = './public/compiler/source/'
    fs.writeFile(`${fPath}${fileName}`,data,function(err){
        if (err){
            return console.error(err);
        }
        console.log("数据写入成功!");
        console.log("--------我是分割线-------------");
        console.log("读取写入的数据!");
        fs.readFile(`${fPath}${fileName}`,function(err,data){
            if(err) {
                return console.error(err);
            }
            console.log("异步读取文件数据: "+data.toString());
        });
    });
};


exports.save = fileSave;