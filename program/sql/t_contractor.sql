--t_response
CREATE TABLE t_response
(
    OBJECT_TYPE VARCHAR(256) NOT NULL,
    x_response VARCHAR(256) NOT NULL
);
CREATE INDEX idx_response_object_type ON t_response (OBJECT_TYPE ASC);
CREATE INDEX idx_response ON t_response (x_response ASC);
--
--t_contractor
CREATE TABLE t_contractor
(
    OBJECT_TYPE VARCHAR(256) NOT NULL,
    x_contractor VARCHAR(256) NOT NULL
);
CREATE INDEX idx_contractor_object_type ON t_contractor (OBJECT_TYPE ASC);
CREATE INDEX idx_contractor ON t_contractor (x_contractor ASC);
