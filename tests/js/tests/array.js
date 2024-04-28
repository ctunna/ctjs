describe("arrays", function () {
  test("empty array", function () {
    expect(Object.length([])).toBe(0);
  });

  test("single element", function () {
    var arr = [1];
    expect(Object.length(arr)).toBe(1);
    expect(arr[0]).toBe(1);
  });

  test("multiple elements", function () {
    var arr = [1, 2, 3];
    expect(Object.length(arr)).toBe(3);
    expect(arr[0]).toBe(1);
    expect(arr[1]).toBe(2);
    expect(arr[2]).toBe(3);
  });
});

