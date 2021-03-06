BEGIN TRANSACTION;
--
CREATE TEMPORARY TABLE tb_violation_tmp
(
ID_VIOLATION INTEGER NOT NULL,
REGNUM VARCHAR(64),
VIOLATION_TYPE VARCHAR(256),
OKRUG VARCHAR(256),
PREF VARCHAR(256),
DISTRICT VARCHAR(256),
CAM_NAME VARCHAR(256),
OBJECT_TYPE VARCHAR(256),
OBJECT_ID VARCHAR(256),
OBJECT_NAME VARCHAR(256),
VIOLATION_DATE VARCHAR(32),
RECORD_DATE VARCHAR(32),
URL VARCHAR(256),
USER_CREATED VARCHAR(256),
NOTE VARCHAR(256)
);
--
INSERT INTO tb_violation_tmp (ID_VIOLATION,REGNUM,VIOLATION_TYPE,OKRUG,PREF,DISTRICT,CAM_NAME,
                                OBJECT_TYPE,OBJECT_ID,OBJECT_NAME,VIOLATION_DATE,RECORD_DATE,URL,USER_CREATED,NOTE)
    SELECT ID_VIOLATION, REGNUM, VIOLATION_TYPE,OKRUG,PREF,DISTRICT,
                CAM_NAME,OBJECT_TYPE,OBJECT_ID,OBJECT_NAME,VIOLATION_DATE,
                RECORD_DATE,URL,USER_CREATED,NOTE FROM TABLE_VIOLATION;
--
DROP TABLE TABLE_VIOLATION;

--06. TABLE_VIOLATION
CREATE TABLE TABLE_VIOLATION
(
ID_VIOLATION INTEGER NOT NULL,
REGNUM VARCHAR(64),
VIOLATION_TYPE VARCHAR(256),
OKRUG VARCHAR(256),
PREF VARCHAR(256),
DISTRICT VARCHAR(256),
CAM_NAME VARCHAR(256),
OBJECT_TYPE VARCHAR(256),
OBJECT_ID VARCHAR(256),
OBJECT_NAME VARCHAR(256),
RESPONSE VARCHAR(256),
CONTRACTOR VARCHAR(256),
VIOLATION_DATE VARCHAR(32),
RECORD_DATE VARCHAR(32),
URL VARCHAR(256),
USER_CREATED VARCHAR(256),
NOTE VARCHAR(256)
);
CREATE UNIQUE INDEX pk_TABLE_VIOLATION ON TABLE_VIOLATION (ID_VIOLATION ASC);
--

INSERT INTO TABLE_VIOLATION (ID_VIOLATION,REGNUM,VIOLATION_TYPE,OKRUG,PREF,DISTRICT,CAM_NAME,
                             OBJECT_TYPE,OBJECT_ID,OBJECT_NAME,VIOLATION_DATE,RECORD_DATE,URL,USER_CREATED,NOTE)
    SELECT ID_VIOLATION,REGNUM,VIOLATION_TYPE,OKRUG,PREF,DISTRICT,CAM_NAME,
           OBJECT_TYPE,OBJECT_ID,OBJECT_NAME,VIOLATION_DATE,RECORD_DATE,URL,USER_CREATED,NOTE FROM tb_violation_tmp;
--
COMMIT TRANSACTION;
