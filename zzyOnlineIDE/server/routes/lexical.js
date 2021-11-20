var express = require('express');
var fs = require('fs');
var router = express.Router();

/* GET lexical listing. */
router.get('/',function(req,res,next){
    var errflag = false;
    fs.exists('./public/compiler/errFiles/lexicalErr.err',function(exist){
        if(exist) {
            res.render('err',{type:'lexical'});
            errflag = true;
        }
    });
    if(!errflag)
        res.render('lexical');
});

module.exports = router;