const PDFDocument = require("pdfkit");
function generareBilet(dateBilet, dataCallback, endCallback) {
    const bilet = new PDFDocument({ bufferPages: 'true', font: 'Courier' });
    bilet.on('data', dataCallback);
    bilet.on('end', endCallback);
    bilet.fontSize(20).text(dateBilet.numeEveniment);
    bilet.end();
}
module.exports = generareBilet;
