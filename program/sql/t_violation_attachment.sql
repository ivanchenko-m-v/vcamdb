--t_violation_attachment
CREATE TABLE t_violation_attachment
(
    i_violation_attachment INTEGER UNIQUE PRIMARY KEY,
    i_violation_id INTEGER,
    x_filename VARCHAR(64),
    bin_attachment BLOB
);
INSERT INTO t_violation_attachment (i_violation_attachment) VALUES (0);
CREATE INDEX idx_violation_id ON t_violation_attachment (i_violation_id ASC);
CREATE INDEX idx_attachment ON t_violation_attachment (i_violation_id, x_filename ASC);
