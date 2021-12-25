<?xml version="1.0" encoding="UTF-8"?>
<xsl:Template match="Client.xml">
    <p>Nom : </p>
    <p><xsl:Value-of select="Name" /></p>
    <br/>
    <p>Prénom : </p>
    <p><xsl:Value-of select="FirstName" /></p>
    <br/>
    <p>Date de Naissance : </p>
    <p><xsl:Value-of select="FirstName" /></p>
    <br/>
    <p>N°Tél : </p>
    <p><xsl:Value-of select="Phone" /></p>
    <br/>
    <p>Adresse : </p><br/>
    <p><xsl:Value-of select="Numero" />     <xsl:Value-of select="NomRue" /></p><br />
    <p><xsl:Value-of select="CodePostal" />     <xsl:Value-of select="Ville" /></p>
</xsl:Template>