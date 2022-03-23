# arduino-smart-switch

Arduino actor for latching/impulse switches (Stromstoßschalter) with webserver and mqtt

## Code formating

Source code formating is done with `clang-format` with the following style setting:

.clang-format configuration file:

```yaml
---
BasedOnStyle: LLVM
AllowShortFunctionsOnASingleLine: Inline
AllowShortBlocksOnASingleLine: Empty
BreakBeforeBraces: Custom
BraceWrapping:
  AfterCaseLabel: false
  AfterClass: false
  AfterControlStatement: Never
  AfterEnum: false
  AfterFunction: false
  AfterNamespace: false
  AfterObjCDeclaration: false
  AfterStruct: false
  AfterUnion: false
  AfterExternBlock: false
  BeforeCatch: true
  BeforeElse: true
  BeforeLambdaBody: false
  BeforeWhile: true
  IndentBraces: false
  SplitEmptyFunction: true
  SplitEmptyRecord: true
  SplitEmptyNamespace: true
ColumnLimit: 120
ConstructorInitializerIndentWidth: 2
ContinuationIndentWidth: 2
FixNamespaceComments: false
IndentPPDirectives: BeforeHash
IndentWidth: 2
NamespaceIndentation: All
TabWidth: 2
UseTab: Never
```
