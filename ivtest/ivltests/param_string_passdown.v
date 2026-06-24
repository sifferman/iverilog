// Regression: a `string` parameter passed as a child parameter override must
// elaborate. Previously this failed ("Unable to bind variable" for the override
// expression, then a string cast error) because the typed elaborate_expr path
// didn't handle a parameter symbol.

module child #(parameter string T = "behavioral") (output wire [1:0] o);
   assign o = (T == "gf180mcu_as_sc_mcu7t3v3") ? 2'd1 : 2'd2;
endmodule

module main #(parameter string T = "behavioral");
   wire [1:0] o;
   child #(.T(T)) child (.o(o));   // string parameter forwarded as a child override
   initial begin
      if (o === 2'd2) $display("PASSED");
      else            $display("FAILED -- o=%0d", o);
      $finish;
   end
endmodule
