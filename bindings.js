var myModule

if (process.env.DEBUG) {
  myModule = require('./build/Debug/ean-native.node')
} else {
  myModule = require('./build/Release/ean-native.node')
}

module.exports = myModule
