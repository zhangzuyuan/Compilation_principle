var express = require('express');
var router = express.Router();

/* GET running page. */
router.get('/', function(req, res, next){
    res.render('run');
});

module.exports = router;