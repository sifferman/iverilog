// Check that array query functions return the bounds of a sign cast or a
// size cast, and 'x for a bit select of a vector or for a dimension that
// does not exist.

module test;

  logic [4:1] packed_vector;
  struct packed {
    logic [7:2] member;
  } packed_struct;
  reg failed;

  `define check(val, exp) \
    if (val !== exp) begin \
      $display("FAILED(%0d): '%s' expected %0d, got %0d", `__LINE__, \
               `"val`", exp, val); \
      failed = 1'b1; \
    end

  initial begin
    failed = 1'b0;

    // $signed(), a sign cast and a size cast have the single dimension
    // [n-1:0], where n is the width of the result.
    `check($left($signed(packed_vector)), 3);
    `check($right($signed(packed_vector)), 0);
    `check($left(signed'(packed_vector)), 3);
    `check($left(6'(packed_vector)), 5);

    // Dimension 2 does not exist.
    `check($left(signed'(packed_vector), 2), 32'bx);
    `check($left(packed_struct.member, 2), 32'bx);

    // The bounds of a bit select are not available.
    `check($left(packed_vector[2]), 32'bx);

    if (!failed) begin
      $display("PASSED");
    end
  end

endmodule
