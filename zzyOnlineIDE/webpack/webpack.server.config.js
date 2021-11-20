const path = require('path');
const webpackNodeExternals = require('webpack-node-externals');

const baseDir = path.resolve(__dirname, '..');


const serverConfig = {
    entry: {
        app: './server/app.js',
    },

    target: 'node',

    // ignore node_modules
    externals: [webpackNodeExternals()],

    // do not polyfill node globals, as we are running this code in node anyways
    context: path.resolve(baseDir),
    node: {
      __dirname: true,
      __filename: true
    },

    output: {
      path: path.resolve(baseDir, './build'),
      filename: '[name].js',
      library: '[name]',
      libraryTarget: 'umd'
    },

    watchOptions: {
      aggregateTimeout: 2000,
      ignored: /node_modules/
    }
};
module.exports = serverConfig;