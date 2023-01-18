const express = require('express');
const router = require('./routes/index.ts');
const app = express();
app.use(router);
app.listen(8080, () => { console.log("TicketMaster PDF Microservice running on 8080."); });
module.exports = app;
