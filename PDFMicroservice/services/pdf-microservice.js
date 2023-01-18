const PDFDocument = require("pdfkit");


function generareBilet(dateBilet, dataCallback, endCallback) {
    const bilet = new PDFDocument({ bufferPages: 'true', font: 'Courier' });

    bilet.on('data', dataCallback);
    bilet.on('end', endCallback);

    bilet.fontSize(20).text(dateBilet.numeEveniment, { align:'center' });
    bilet.fontSize(18).text(`Zona: ${dateBilet.zonaEveniment}`, { align: 'center' });
    bilet.fontSize(12).text(`Rand: ${dateBilet.randEveniment} - Loc: ${dateBilet.locEveniment}`, { align: 'center' });

    bilet.moveDown(3);

    bilet.fontSize(8).text("Distractie placuta!");
    bilet.fontSize(8).text("Bilet generat de TicketMaster.");

    bilet.end();
}

module.exports = generareBilet;