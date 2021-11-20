const glob = require('glob');
const path = require('path');
const webpack = require('webpack');

const baseDir = path.resolve(__dirname, '..' );

function getClientEntries (){
    const files = glob.sync('./client/views/*/*View.jsx');
    const entries = files.reduce((obj,fname) => {
        let name = fname.split('/')[4]; // name = HomeView.jsx
        name = name.split('.')[0];
        obj[name] = fname;
        return obj;
    },{});
    return entries;
}

const entries = getClientEntries();

const clientConfig = {
    entry:entries,
    output: {
        path: path.resolve(baseDir,'public'),
        filename: 'javascripts/[name].bunndle.js',
        publicPath:'/'
    },
    module:{
        rules: [  
            {  
              test: /\.jsx?$/,  
              loader: 'babel-loader',
              include: [
                path.resolve(baseDir, './client')
              ],
              exclude: /node_modules/,
              query: {  
                presets: ['react', 'es2015'],
                compact: false
              }
            },
            { test: /\.css$/,
              include: [ path.resolve(baseDir, './client') ],
              loader: 'style-loader!css-loader',
              exclude: '/node_modules/'
            }
        ]  
    },

    watchOptions: {
        aggregateTimeout: 2000,
        ignored: /node_modules/
    }
}

module.exports = clientConfig;
