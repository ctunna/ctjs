describe("strings", function () {
  test("integer coercion", function () {
    expect(1 + "").toBe("1");
    expect("" + 1).toBe("1");
  });

  test("bool coercion", function () {
    expect(true + "").toBe("true");
    expect("" + false).toBe("false");
  });

  test("concatenation", function() {
    expect("a" + "b").toBe("ab");
    expect("a" + 1).toBe("a1");
    expect("" + "").toBe("");
    expect("a" + "").toBe("a");
  });
});
