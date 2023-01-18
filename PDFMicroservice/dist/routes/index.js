const express = require('express');
const generareBilet = require("../services/pdf-microservice.ts");
const yup = require("yup");
const router = express.Router();
const bileteSchema = yup.object({});
/* GET home page. */
router.get('/generare-bilet', function (req, res, next) {
    const stream = res.writeHead(200, {
        'Content-Type': 'application/pdf',
        'Content-Disposition': `attachment;filename=bilet.pdf`,
    });
    generareBilet((chunk) => stream.write(chunk), () => stream.end());
});
module.exports = router;
