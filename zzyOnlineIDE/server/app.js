var createError = require('http-errors');
var express = require('express');
var path = require('path');
var cookieParser = require('cookie-parser');
var logger = require('morgan');

var indexRouter = require('./routes/index');
var usersRouter = require('./routes/users');
var lexicalRouter = require('./routes/lexical');
var parserRouter = require('./routes/parser');
var runRouter = require('./routes/run');

const baseDir = path.resolve(__dirname, '../');
const serverDir = path.join(baseDir, 'server');
const publicDir = path.join(baseDir, 'public');

var app = express();

// view engine setup
app.set('views', path.join(serverDir, 'views'));
app.set('view engine', 'ejs');

app.use(logger('dev'));
app.use(express.json());
app.use(express.urlencoded({extended:false}));
app.use(cookieParser());
app.use(express.static(publicDir));

app.use('/',indexRouter);
app.use('/users',usersRouter);
app.use('/lexical',lexicalRouter);
app.use('/parser',parserRouter);
app.use('/run',runRouter);

// catch 404 and forward to error handler
app.use(function(req, res, next) {
    next(createError(404));
});

// error handler
app.use(function(err, req, res, next) {
    // set locals, only providing error in development
    res.locals.message = err.message;
    res.locals.error = req.app.get('env') === 'development' ? err : {};
  
    // render the error page
    res.status(err.status || 500);
    res.render('error');
});

module.exports = app;