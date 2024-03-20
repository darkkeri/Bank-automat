-- MySQL dump 10.13  Distrib 8.2.0, for Win64 (x86_64)
--
-- Host: localhost    Database: arviointitietokanta
-- ------------------------------------------------------
-- Server version	8.2.0

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8mb4 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Current Database: `arviointitietokanta`
--

CREATE DATABASE /*!32312 IF NOT EXISTS*/ `arviointitietokanta` /*!40100 DEFAULT CHARACTER SET utf8mb3 */ /*!80016 DEFAULT ENCRYPTION='N' */;

USE `arviointitietokanta`;

--
-- Table structure for table `arviointi`
--

DROP TABLE IF EXISTS `arviointi`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `arviointi` (
  `idArviointi` int NOT NULL AUTO_INCREMENT,
  `Paivamaara` date NOT NULL,
  `Arvosana` tinyint NOT NULL,
  `idOpiskelija` int NOT NULL,
  `idOpintojakso` int NOT NULL,
  PRIMARY KEY (`idArviointi`),
  KEY `fk_Opintojakso_has_Opiskelija_Opiskelija1_idx` (`idOpiskelija`),
  KEY `fk_Opintojakso_has_Opiskelija_Opintojakso_idx` (`idOpintojakso`),
  CONSTRAINT `fk_Opintojakso_has_Opiskelija_Opintojakso` FOREIGN KEY (`idOpintojakso`) REFERENCES `opintojakso` (`idOpintojakso`),
  CONSTRAINT `fk_Opintojakso_has_Opiskelija_Opiskelija1` FOREIGN KEY (`idOpiskelija`) REFERENCES `opiskelija` (`idOpiskelija`)
) ENGINE=InnoDB AUTO_INCREMENT=14 DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `arviointi`
--

LOCK TABLES `arviointi` WRITE;
/*!40000 ALTER TABLE `arviointi` DISABLE KEYS */;
INSERT INTO `arviointi` VALUES (1,'2014-09-05',1,1,1),(2,'2014-09-05',2,2,2),(3,'2014-09-05',3,3,3),(4,'2014-09-05',4,4,4),(5,'2014-09-05',5,5,5),(6,'2014-09-05',1,1,2),(7,'2014-09-05',2,2,3),(8,'2014-09-05',3,3,4),(9,'2014-09-05',4,4,5),(10,'2014-09-05',5,5,1),(12,'2014-09-05',0,1,5),(13,'2024-02-11',3,1,1);
/*!40000 ALTER TABLE `arviointi` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `opintojakso`
--

DROP TABLE IF EXISTS `opintojakso`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `opintojakso` (
  `idOpintojakso` int NOT NULL AUTO_INCREMENT,
  `Koodi` varchar(45) NOT NULL,
  `Laajuus` tinyint NOT NULL,
  `Nimi` varchar(45) NOT NULL,
  PRIMARY KEY (`idOpintojakso`)
) ENGINE=InnoDB AUTO_INCREMENT=9 DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `opintojakso`
--

LOCK TABLES `opintojakso` WRITE;
/*!40000 ALTER TABLE `opintojakso` DISABLE KEYS */;
INSERT INTO `opintojakso` VALUES (1,'T20041',3,'Tietokannat'),(2,'T20042',3,'Liike-elaman tapatietous'),(3,'T20043',3,'Fysiikka 3'),(4,'T20044',6,'Elektroniikan perusteet'),(5,'T20045',5,'Kellarihumppa'),(6,'T20046',3,'Matematiikka 2'),(7,'T20047',3,'Ruotsin kieli'),(8,'T20048',3,'VHDL-kieli');
/*!40000 ALTER TABLE `opintojakso` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `opiskelija`
--

DROP TABLE IF EXISTS `opiskelija`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `opiskelija` (
  `idOpiskelija` int NOT NULL AUTO_INCREMENT,
  `Etunimi` varchar(45) NOT NULL,
  `Sukunimi` varchar(45) NOT NULL,
  `Osoite` varchar(45) NOT NULL,
  `Luokkatunnus` varchar(45) NOT NULL,
  PRIMARY KEY (`idOpiskelija`)
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `opiskelija`
--

LOCK TABLES `opiskelija` WRITE;
/*!40000 ALTER TABLE `opiskelija` DISABLE KEYS */;
INSERT INTO `opiskelija` VALUES (1,'Aku','Ankka','Ankkalinna 313','TTE3SNH'),(2,'Roope','Ankka','Ankkalinna 314','TTE3SNH'),(3,'Iines','Ankka','Ankkalinna 315','TTE4SNL'),(4,'Mikki','Hiiri','Ankkalinna 316','TTE2SNO'),(5,'Hessu','Hopo','Ankkalinna 317','TTE2SNO');
/*!40000 ALTER TABLE `opiskelija` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2024-03-10 23:26:11
