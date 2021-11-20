(function webpackUniversalModuleDefinition(root, factory) {
	if(typeof exports === 'object' && typeof module === 'object')
		module.exports = factory();
	else if(typeof define === 'function' && define.amd)
		define([], factory);
	else if(typeof exports === 'object')
		exports["app"] = factory();
	else
		root["app"] = factory();
})(global, function() {
return /******/ (function(modules) { // webpackBootstrap
/******/ 	// The module cache
/******/ 	var installedModules = {};
/******/
/******/ 	// The require function
/******/ 	function __webpack_require__(moduleId) {
/******/
/******/ 		// Check if module is in cache
/******/ 		if(installedModules[moduleId]) {
/******/ 			return installedModules[moduleId].exports;
/******/ 		}
/******/ 		// Create a new module (and put it into the cache)
/******/ 		var module = installedModules[moduleId] = {
/******/ 			i: moduleId,
/******/ 			l: false,
/******/ 			exports: {}
/******/ 		};
/******/
/******/ 		// Execute the module function
/******/ 		modules[moduleId].call(module.exports, module, module.exports, __webpack_require__);
/******/
/******/ 		// Flag the module as loaded
/******/ 		module.l = true;
/******/
/******/ 		// Return the exports of the module
/******/ 		return module.exports;
/******/ 	}
/******/
/******/
/******/ 	// expose the modules object (__webpack_modules__)
/******/ 	__webpack_require__.m = modules;
/******/
/******/ 	// expose the module cache
/******/ 	__webpack_require__.c = installedModules;
/******/
/******/ 	// define getter function for harmony exports
/******/ 	__webpack_require__.d = function(exports, name, getter) {
/******/ 		if(!__webpack_require__.o(exports, name)) {
/******/ 			Object.defineProperty(exports, name, { enumerable: true, get: getter });
/******/ 		}
/******/ 	};
/******/
/******/ 	// define __esModule on exports
/******/ 	__webpack_require__.r = function(exports) {
/******/ 		if(typeof Symbol !== 'undefined' && Symbol.toStringTag) {
/******/ 			Object.defineProperty(exports, Symbol.toStringTag, { value: 'Module' });
/******/ 		}
/******/ 		Object.defineProperty(exports, '__esModule', { value: true });
/******/ 	};
/******/
/******/ 	// create a fake namespace object
/******/ 	// mode & 1: value is a module id, require it
/******/ 	// mode & 2: merge all properties of value into the ns
/******/ 	// mode & 4: return value when already ns object
/******/ 	// mode & 8|1: behave like require
/******/ 	__webpack_require__.t = function(value, mode) {
/******/ 		if(mode & 1) value = __webpack_require__(value);
/******/ 		if(mode & 8) return value;
/******/ 		if((mode & 4) && typeof value === 'object' && value && value.__esModule) return value;
/******/ 		var ns = Object.create(null);
/******/ 		__webpack_require__.r(ns);
/******/ 		Object.defineProperty(ns, 'default', { enumerable: true, value: value });
/******/ 		if(mode & 2 && typeof value != 'string') for(var key in value) __webpack_require__.d(ns, key, function(key) { return value[key]; }.bind(null, key));
/******/ 		return ns;
/******/ 	};
/******/
/******/ 	// getDefaultExport function for compatibility with non-harmony modules
/******/ 	__webpack_require__.n = function(module) {
/******/ 		var getter = module && module.__esModule ?
/******/ 			function getDefault() { return module['default']; } :
/******/ 			function getModuleExports() { return module; };
/******/ 		__webpack_require__.d(getter, 'a', getter);
/******/ 		return getter;
/******/ 	};
/******/
/******/ 	// Object.prototype.hasOwnProperty.call
/******/ 	__webpack_require__.o = function(object, property) { return Object.prototype.hasOwnProperty.call(object, property); };
/******/
/******/ 	// __webpack_public_path__
/******/ 	__webpack_require__.p = "";
/******/
/******/
/******/ 	// Load entry module and return exports
/******/ 	return __webpack_require__(__webpack_require__.s = "./server/app.js");
/******/ })
/************************************************************************/
/******/ ({

/***/ "./server/app.js":
/*!***********************!*\
  !*** ./server/app.js ***!
  \***********************/
/*! no static exports found */
/***/ (function(module, exports, __webpack_require__) {

eval("/* WEBPACK VAR INJECTION */(function(__dirname) {var createError = __webpack_require__(/*! http-errors */ \"http-errors\");\r\nvar express = __webpack_require__(/*! express */ \"express\");\r\nvar path = __webpack_require__(/*! path */ \"path\");\r\nvar cookieParser = __webpack_require__(/*! cookie-parser */ \"cookie-parser\");\r\nvar logger = __webpack_require__(/*! morgan */ \"morgan\");\r\n\r\nvar indexRouter = __webpack_require__(/*! ./routes/index */ \"./server/routes/index.js\");\r\nvar usersRouter = __webpack_require__(/*! ./routes/users */ \"./server/routes/users.js\");\r\nvar lexicalRouter = __webpack_require__(/*! ./routes/lexical */ \"./server/routes/lexical.js\");\r\nvar parserRouter = __webpack_require__(/*! ./routes/parser */ \"./server/routes/parser.js\");\r\nvar runRouter = __webpack_require__(/*! ./routes/run */ \"./server/routes/run.js\");\r\n\r\nconst baseDir = path.resolve(__dirname, '../');\r\nconst serverDir = path.join(baseDir, 'server');\r\nconst publicDir = path.join(baseDir, 'public');\r\n\r\nvar app = express();\r\n\r\n// view engine setup\r\napp.set('views', path.join(serverDir, 'views'));\r\napp.set('view engine', 'ejs');\r\n\r\napp.use(logger('dev'));\r\napp.use(express.json());\r\napp.use(express.urlencoded({extended:false}));\r\napp.use(cookieParser());\r\napp.use(express.static(publicDir));\r\n\r\napp.use('/',indexRouter);\r\napp.use('/users',usersRouter);\r\napp.use('/lexical',lexicalRouter);\r\napp.use('/parser',parserRouter);\r\napp.use('/run',runRouter);\r\n\r\n// catch 404 and forward to error handler\r\napp.use(function(req, res, next) {\r\n    next(createError(404));\r\n});\r\n\r\n// error handler\r\napp.use(function(err, req, res, next) {\r\n    // set locals, only providing error in development\r\n    res.locals.message = err.message;\r\n    res.locals.error = req.app.get('env') === 'development' ? err : {};\r\n  \r\n    // render the error page\r\n    res.status(err.status || 500);\r\n    res.render('error');\r\n});\r\n\r\nmodule.exports = app;\n/* WEBPACK VAR INJECTION */}.call(this, \"server\"))\n\n//# sourceURL=webpack://%5Bname%5D/./server/app.js?");

/***/ }),

/***/ "./server/models/receive/fileSaver.js":
/*!********************************************!*\
  !*** ./server/models/receive/fileSaver.js ***!
  \********************************************/
/*! no static exports found */
/***/ (function(module, exports, __webpack_require__) {

eval("var fs = __webpack_require__(/*! fs */ \"fs\");\r\n\r\nvar fileSave = function(data,fileName){\r\n    var fPath = './public/compiler/source/'\r\n    fs.writeFile(`${fPath}${fileName}`,data,function(err){\r\n        if (err){\r\n            return console.error(err);\r\n        }\r\n        console.log(\"数据写入成功!\");\r\n        console.log(\"--------我是分割线-------------\");\r\n        console.log(\"读取写入的数据!\");\r\n        fs.readFile(`${fPath}${fileName}`,function(err,data){\r\n            if(err) {\r\n                return console.error(err);\r\n            }\r\n            console.log(\"异步读取文件数据: \"+data.toString());\r\n        });\r\n    });\r\n};\r\n\r\n\r\nexports.save = fileSave;\n\n//# sourceURL=webpack://%5Bname%5D/./server/models/receive/fileSaver.js?");

/***/ }),

/***/ "./server/models/receive/runCompiler.js":
/*!**********************************************!*\
  !*** ./server/models/receive/runCompiler.js ***!
  \**********************************************/
/*! no static exports found */
/***/ (function(module, exports, __webpack_require__) {

eval("var fs = __webpack_require__(/*! fs */ \"fs\");\r\nvar exec = __webpack_require__(/*! child_process */ \"child_process\").execFile;\r\n\r\nvar runCompiler = function(fileName){\r\n    console.log(\"hello exe\");\r\n    var fPath = './public/compiler/out/'\r\n    exec(`${fPath}${fileName}`,function(err, data) {\r\n        console.log(data);\r\n    });\r\n};\r\n\r\n\r\nexports.run = runCompiler;\n\n//# sourceURL=webpack://%5Bname%5D/./server/models/receive/runCompiler.js?");

/***/ }),

/***/ "./server/routes/index.js":
/*!********************************!*\
  !*** ./server/routes/index.js ***!
  \********************************/
/*! no static exports found */
/***/ (function(module, exports, __webpack_require__) {

eval("var express = __webpack_require__(/*! express */ \"express\");\r\nvar fileSaver = __webpack_require__(/*! ../models/receive/fileSaver.js */ \"./server/models/receive/fileSaver.js\");\r\nvar runCompiler = __webpack_require__(/*! ../models/receive/runCompiler.js */ \"./server/models/receive/runCompiler.js\")\r\nvar router = express.Router();\r\n\r\n\r\n\r\n/* GET home page. */\r\nrouter.get('/',function(req, res, next){\r\n    res.render('index',{title: 'Express'});\r\n});\r\n\r\nrouter.post('/',function(req, res, next){\r\n    // console.log(\"start save\");\r\n    // fileSaver.save(req.body.code, 'code.source', );\r\n    // console.log(\"end save\");\r\n    var myPromise = new Promise(function(resolve,reject){\r\n        fileSaver.save(req.body.code, 'code.source', );\r\n        console.log(\"end save\");\r\n        resolve(\"start run\")\r\n    });\r\n\r\n    myPromise.then(function(successMessage){\r\n        console.log(successMessage);\r\n        runCompiler.run(\"main.exe\");\r\n        resolve(\"end run\");\r\n        \r\n    });\r\n    res.render('receive');\r\n    // console.log(\"start exe\");\r\n    // runCompiler.run(\"main.exe\");\r\n    // console.log(\"end exe\");\r\n\r\n    \r\n});\r\n\r\n\r\n\r\nmodule.exports = router;\n\n//# sourceURL=webpack://%5Bname%5D/./server/routes/index.js?");

/***/ }),

/***/ "./server/routes/lexical.js":
/*!**********************************!*\
  !*** ./server/routes/lexical.js ***!
  \**********************************/
/*! no static exports found */
/***/ (function(module, exports, __webpack_require__) {

eval("var express = __webpack_require__(/*! express */ \"express\");\r\nvar fs = __webpack_require__(/*! fs */ \"fs\");\r\nvar router = express.Router();\r\n\r\n/* GET lexical listing. */\r\nrouter.get('/',function(req,res,next){\r\n    var errflag = false;\r\n    fs.exists('./public/compiler/errFiles/lexicalErr.err',function(exist){\r\n        if(exist) {\r\n            res.render('err',{type:'lexical'});\r\n            errflag = true;\r\n        }\r\n    });\r\n    if(!errflag)\r\n        res.render('lexical');\r\n});\r\n\r\nmodule.exports = router;\n\n//# sourceURL=webpack://%5Bname%5D/./server/routes/lexical.js?");

/***/ }),

/***/ "./server/routes/parser.js":
/*!*********************************!*\
  !*** ./server/routes/parser.js ***!
  \*********************************/
/*! no static exports found */
/***/ (function(module, exports, __webpack_require__) {

eval("var express = __webpack_require__(/*! express */ \"express\");\r\nvar router = express.Router();\r\n\r\nrouter.get('/', function(req, res, next){\r\n    res.render('parser');\r\n});\r\n\r\nmodule.exports = router;\n\n//# sourceURL=webpack://%5Bname%5D/./server/routes/parser.js?");

/***/ }),

/***/ "./server/routes/run.js":
/*!******************************!*\
  !*** ./server/routes/run.js ***!
  \******************************/
/*! no static exports found */
/***/ (function(module, exports, __webpack_require__) {

eval("var express = __webpack_require__(/*! express */ \"express\");\r\nvar router = express.Router();\r\n\r\n/* GET running page. */\r\nrouter.get('/', function(req, res, next){\r\n    res.render('run');\r\n});\r\n\r\nmodule.exports = router;\n\n//# sourceURL=webpack://%5Bname%5D/./server/routes/run.js?");

/***/ }),

/***/ "./server/routes/users.js":
/*!********************************!*\
  !*** ./server/routes/users.js ***!
  \********************************/
/*! no static exports found */
/***/ (function(module, exports, __webpack_require__) {

eval("var express = __webpack_require__(/*! express */ \"express\");\r\nvar router = express.Router();\r\n\r\n/* GET users listing. */\r\nrouter.get('/', function(req, res, next){\r\n    res.send('respond with a resource');\r\n});\r\n\r\nmodule.exports = router;\n\n//# sourceURL=webpack://%5Bname%5D/./server/routes/users.js?");

/***/ }),

/***/ "child_process":
/*!********************************!*\
  !*** external "child_process" ***!
  \********************************/
/*! no static exports found */
/***/ (function(module, exports) {

eval("module.exports = require(\"child_process\");\n\n//# sourceURL=webpack://%5Bname%5D/external_%22child_process%22?");

/***/ }),

/***/ "cookie-parser":
/*!********************************!*\
  !*** external "cookie-parser" ***!
  \********************************/
/*! no static exports found */
/***/ (function(module, exports) {

eval("module.exports = require(\"cookie-parser\");\n\n//# sourceURL=webpack://%5Bname%5D/external_%22cookie-parser%22?");

/***/ }),

/***/ "express":
/*!**************************!*\
  !*** external "express" ***!
  \**************************/
/*! no static exports found */
/***/ (function(module, exports) {

eval("module.exports = require(\"express\");\n\n//# sourceURL=webpack://%5Bname%5D/external_%22express%22?");

/***/ }),

/***/ "fs":
/*!*********************!*\
  !*** external "fs" ***!
  \*********************/
/*! no static exports found */
/***/ (function(module, exports) {

eval("module.exports = require(\"fs\");\n\n//# sourceURL=webpack://%5Bname%5D/external_%22fs%22?");

/***/ }),

/***/ "http-errors":
/*!******************************!*\
  !*** external "http-errors" ***!
  \******************************/
/*! no static exports found */
/***/ (function(module, exports) {

eval("module.exports = require(\"http-errors\");\n\n//# sourceURL=webpack://%5Bname%5D/external_%22http-errors%22?");

/***/ }),

/***/ "morgan":
/*!*************************!*\
  !*** external "morgan" ***!
  \*************************/
/*! no static exports found */
/***/ (function(module, exports) {

eval("module.exports = require(\"morgan\");\n\n//# sourceURL=webpack://%5Bname%5D/external_%22morgan%22?");

/***/ }),

/***/ "path":
/*!***********************!*\
  !*** external "path" ***!
  \***********************/
/*! no static exports found */
/***/ (function(module, exports) {

eval("module.exports = require(\"path\");\n\n//# sourceURL=webpack://%5Bname%5D/external_%22path%22?");

/***/ })

/******/ });
});