{$mode objfpc}{$assertions on}{$r+}{$h+}

var
  vowels: set of Char = ['a', 'e', 'i', 'o', 'u', 'y'];
  consonants: set of Char = ['a'..'z'];
var
  res: string[100];
  N, M: Integer;
  s: array of String;
  cnt: Integer = 0;

procedure Rec(k: Integer; ch: Char);
var
  i, len: Integer;
begin
  res[k] := ch;
  Ord(res[0]) := k;
  for i := 0 to M - 1 do begin
    len := Length(s[i]);
    if (len <= k) and (Copy(res, k - len + 1, len) = s[i]) then exit;
  end;
  if k = N then begin cnt += 1; exit; end;

  if res[k] in vowels then
    for ch in consonants do
      Rec(k + 1, ch)
  else
    for ch in vowels do
      Rec(k + 1, ch);
end;

var
  i: Integer;
  ch: Char;
begin
  AssignFile(input, 'input.txt'); Reset(input);
  AssignFile(output, 'output.txt'); Rewrite(output);
  Readln(N, M);
  SetLength(s, M);
  consonants -= vowels;
  for i := 0 to M - 1 do Readln(s[i]);
  for ch := 'a' to 'z' do
    Rec(1, ch);
  Writeln(cnt);
end.
