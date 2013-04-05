try {
    module.exports = require('./build/Release/getifaddrs');
} catch (e) {
    try {
        module.exports = require('./build/default/getifaddrs');
    } catch (e) { 
        console.error('getifaddrs.node seems to not have been built. Run npm install.');
        throw e;
    }
}