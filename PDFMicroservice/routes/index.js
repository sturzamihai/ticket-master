const express = require('express');
const generareBilet = require("../services/pdf-microservice.js");
const yup = require("yup");

const router = express.Router();

const bileteSchema = yup.object({
    numeEveniment: yup.string().required(),
    zonaEveniment: yup.string().required(),
    randEveniment: yup.string().required(),
    locEveniment: yup.string().required(),
});

/* GET home page. */
router.get('/generare-bilet', async function(req, res, next) {
    try {
        const parsedQuery = await bileteSchema.validate(req.query);

        const stream = res.writeHead(200, {
            'Content-Type': 'application/pdf',
            'Content-Disposition': `attachment;filename=bilet.pdf`,
        });

        generareBilet(
            parsedQuery,
            (chunk) => stream.write(chunk),
            () => stream.end()
        );
    }
    catch (e) {
        res.status(400).send("Invalid parameters received");
    }
});

module.exports = router;
