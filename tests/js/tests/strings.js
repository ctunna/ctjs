describe("strings", function () {
  test("integer coercion", function () {
    expect(1 + "").toBe("1");
    expect("" + 1).toBe("1");
  });
});
