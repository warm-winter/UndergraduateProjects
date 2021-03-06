/* Generated by a program written by John Boyland */
#include "tree.h"
#include "aps-tree.handcode.h"
/* Automatically generated file */

/* Typedefs for the phyla of language: ABSTRACT_APS */
typedef struct Signature__struct *Signature;
typedef struct Type__struct *Type;
typedef struct Expression__struct *Expression;
typedef struct Pattern__struct *Pattern;
typedef struct SignatureDecl__struct *SignatureDecl;
typedef struct TypeDecl__struct *TypeDecl;
typedef struct ValueDecl__struct *ValueDecl;
typedef struct PatternDecl__struct *PatternDecl;
typedef struct Program__struct *Program;
typedef struct Unit__struct *Unit;
typedef struct Declaration__struct *Declaration;
typedef struct Renaming__struct *Renaming;
typedef struct Match__struct *Match;
typedef struct Direction__struct *Direction;
typedef struct Default__struct *Default;
typedef struct Units__struct *Units;
typedef struct Declarations__struct *Declarations;
typedef struct Matches__struct *Matches;
typedef struct Renamings__struct *Renamings;
typedef struct Signatures__struct *Signatures;
typedef struct Types__struct *Types;
typedef struct Expressions__struct *Expressions;
typedef struct Patterns__struct *Patterns;
typedef struct Formals__struct *Formals;
typedef struct TypeFormals__struct *TypeFormals;
typedef struct Actuals__struct *Actuals;
typedef struct TypeActuals__struct *TypeActuals;
typedef struct PatternActuals__struct *PatternActuals;

/* Declaration for lists used in this language */


/* the phylum key */

extern enum KEYTYPE_Phylum {
  KEYSignature,
  KEYType,
  KEYExpression,
  KEYPattern,
  KEYSignatureDecl,
  KEYTypeDecl,
  KEYValueDecl,
  KEYPatternDecl,
  KEYProgram,
  KEYUnit,
  KEYDeclaration,
  KEYRenaming,
  KEYMatch,
  KEYDirection,
  KEYDefault,
  KEYUnits,
  KEYDeclarations,
  KEYMatches,
  KEYRenamings,
  KEYSignatures,
  KEYTypes,
  KEYExpressions,
  KEYPatterns,
  KEYFormals,
  KEYTypeFormals,
  KEYActuals,
  KEYTypeActuals,
  KEYPatternActuals,
  KEYNone
} tnode_phylum(void *);

/* Phyla, constructors and accessors */

extern enum KEYTYPE_Signature {
  KEYsig_name,
  KEYno_sig,
  KEYsig_inst,
  KEYqual_sig,
  KEYvar_sig,
  KEYconstant_sig,
  KEYmodule_sig,
  KEYfixed_sig
} Signature_KEY(Signature);
extern Signature copy_Signature(Signature);
extern void assert_Signature(Signature);

extern enum KEYTYPE_Type {
  KEYtype_name,
  KEYno_type,
  KEYtype_inst,
  KEYqual_type,
  KEYremote_type,
  KEYordered_set_type,
  KEYset_type,
  KEYlist_type,
  KEYfunction_type
} Type_KEY(Type);
extern Type copy_Type(Type);
extern void assert_Type(Type);

extern enum KEYTYPE_Expression {
  KEYvalue_name,
  KEYvalue_inst,
  KEYqual_value,
  KEYinteger_const,
  KEYstring_const,
  KEYchar_const,
  KEYundefined,
  KEYno_expr,
  KEYfuncall,
  KEYreduce,
  KEYsequence,
  KEYconstructor_key,
  KEYsignature_value,
  KEYtype_value,
  KEYpattern_value,
  KEYrepeat,
  KEYguarded,
  KEYcontrolled
} Expression_KEY(Expression);
extern Expression copy_Expression(Expression);
extern void assert_Expression(Expression);

extern enum KEYTYPE_Pattern {
  KEYpattern_name,
  KEYno_pattern,
  KEYpattern_inst,
  KEYqual_pattern,
  KEYsimple_pattern,
  KEYpattern_actual,
  KEYsequence_pattern,
  KEYrest_pattern,
  KEYchoice_pattern,
  KEYand_pattern,
  KEYpattern_var,
  KEYcondition
} Pattern_KEY(Pattern);
extern Pattern copy_Pattern(Pattern);
extern void assert_Pattern(Pattern);

extern enum KEYTYPE_SignatureDecl {
  KEYa_signature
} SignatureDecl_KEY(SignatureDecl);
extern SignatureDecl copy_SignatureDecl(SignatureDecl);
extern void assert_SignatureDecl(SignatureDecl);

extern enum KEYTYPE_TypeDecl {
  KEYa_type
} TypeDecl_KEY(TypeDecl);
extern TypeDecl copy_TypeDecl(TypeDecl);
extern void assert_TypeDecl(TypeDecl);

extern enum KEYTYPE_ValueDecl {
  KEYa_value
} ValueDecl_KEY(ValueDecl);
extern ValueDecl copy_ValueDecl(ValueDecl);
extern void assert_ValueDecl(ValueDecl);

extern enum KEYTYPE_PatternDecl {
  KEYa_pattern
} PatternDecl_KEY(PatternDecl);
extern PatternDecl copy_PatternDecl(PatternDecl);
extern void assert_PatternDecl(PatternDecl);

extern enum KEYTYPE_Program {
  KEYprogram
} Program_KEY(Program);
extern Program copy_Program(Program);
extern void assert_Program(Program);

extern enum KEYTYPE_Unit {
  KEYno_unit,
  KEYwith_unit,
  KEYdecl_unit
} Unit_KEY(Unit);
extern Unit copy_Unit(Unit);
extern void assert_Unit(Unit);

extern enum KEYTYPE_Declaration {
  KEYno_decl,
  KEYmodule_decl,
  KEYsignature_decl,
  KEYphylum_decl,
  KEYconstructor_decl,
  KEYattribute_decl,
  KEYtype_decl,
  KEYfunction_decl,
  KEYprocedure_decl,
  KEYtop_level_match,
  KEYvalue_decl,
  KEYpattern_decl,
  KEYinheritance,
  KEYpragma_decl,
  KEYstmts,
  KEYeffect,
  KEYassign,
  KEYif_stmt,
  KEYfor_in_stmt,
  KEYfor_on_stmt,
  KEYfor_stmt,
  KEYcase_stmt
} Declaration_KEY(Declaration);
extern Declaration copy_Declaration(Declaration);
extern void assert_Declaration(Declaration);

extern enum KEYTYPE_Renaming {
  KEYno_renaming,
  KEYsignature_replacement,
  KEYtype_replacement,
  KEYvalue_replacement,
  KEYpattern_replacement,
  KEYsignature_renaming,
  KEYtype_renaming,
  KEYvalue_renaming,
  KEYpattern_renaming
} Renaming_KEY(Renaming);
extern Renaming copy_Renaming(Renaming);
extern void assert_Renaming(Renaming);

extern enum KEYTYPE_Match {
  KEYmatcher
} Match_KEY(Match);
extern Match copy_Match(Match);
extern void assert_Match(Match);

extern enum KEYTYPE_Direction {
  KEYno_direction,
  KEYcollection_,
  KEYcircular_
} Direction_KEY(Direction);
extern Direction copy_Direction(Direction);
extern void assert_Direction(Direction);

extern enum KEYTYPE_Default {
  KEYsimple,
  KEYcomposite,
  KEYlattice,
  KEYno_default
} Default_KEY(Default);
extern Default copy_Default(Default);
extern void assert_Default(Default);

extern enum KEYTYPE_Units {
  KEYnil_Units,
  KEYlist_Units,
  KEYappend_Units
} Units_KEY(Units);
extern Units copy_Units(Units);
extern void assert_Units(Units);

extern Units nil_Units();

extern Units list_Units(Unit);
extern Unit list_Units_elem(Units);

extern Units append_Units(Units,Units);
extern Units append_Units_l1(Units);
extern Units append_Units_l2(Units);

extern enum KEYTYPE_Declarations {
  KEYnil_Declarations,
  KEYlist_Declarations,
  KEYappend_Declarations
} Declarations_KEY(Declarations);
extern Declarations copy_Declarations(Declarations);
extern void assert_Declarations(Declarations);

extern Declarations nil_Declarations();

extern Declarations list_Declarations(Declaration);
extern Declaration list_Declarations_elem(Declarations);

extern Declarations append_Declarations(Declarations,Declarations);
extern Declarations append_Declarations_l1(Declarations);
extern Declarations append_Declarations_l2(Declarations);

extern enum KEYTYPE_Matches {
  KEYnil_Matches,
  KEYlist_Matches,
  KEYappend_Matches
} Matches_KEY(Matches);
extern Matches copy_Matches(Matches);
extern void assert_Matches(Matches);

extern Matches nil_Matches();

extern Matches list_Matches(Match);
extern Match list_Matches_elem(Matches);

extern Matches append_Matches(Matches,Matches);
extern Matches append_Matches_l1(Matches);
extern Matches append_Matches_l2(Matches);

extern enum KEYTYPE_Renamings {
  KEYnil_Renamings,
  KEYlist_Renamings,
  KEYappend_Renamings
} Renamings_KEY(Renamings);
extern Renamings copy_Renamings(Renamings);
extern void assert_Renamings(Renamings);

extern Renamings nil_Renamings();

extern Renamings list_Renamings(Renaming);
extern Renaming list_Renamings_elem(Renamings);

extern Renamings append_Renamings(Renamings,Renamings);
extern Renamings append_Renamings_l1(Renamings);
extern Renamings append_Renamings_l2(Renamings);

extern enum KEYTYPE_Signatures {
  KEYnil_Signatures,
  KEYlist_Signatures,
  KEYappend_Signatures
} Signatures_KEY(Signatures);
extern Signatures copy_Signatures(Signatures);
extern void assert_Signatures(Signatures);

extern Signatures nil_Signatures();

extern Signatures list_Signatures(Signature);
extern Signature list_Signatures_elem(Signatures);

extern Signatures append_Signatures(Signatures,Signatures);
extern Signatures append_Signatures_l1(Signatures);
extern Signatures append_Signatures_l2(Signatures);

extern enum KEYTYPE_Types {
  KEYnil_Types,
  KEYlist_Types,
  KEYappend_Types
} Types_KEY(Types);
extern Types copy_Types(Types);
extern void assert_Types(Types);

extern Types nil_Types();

extern Types list_Types(Type);
extern Type list_Types_elem(Types);

extern Types append_Types(Types,Types);
extern Types append_Types_l1(Types);
extern Types append_Types_l2(Types);

extern enum KEYTYPE_Expressions {
  KEYnil_Expressions,
  KEYlist_Expressions,
  KEYappend_Expressions
} Expressions_KEY(Expressions);
extern Expressions copy_Expressions(Expressions);
extern void assert_Expressions(Expressions);

extern Expressions nil_Expressions();

extern Expressions list_Expressions(Expression);
extern Expression list_Expressions_elem(Expressions);

extern Expressions append_Expressions(Expressions,Expressions);
extern Expressions append_Expressions_l1(Expressions);
extern Expressions append_Expressions_l2(Expressions);

extern enum KEYTYPE_Patterns {
  KEYnil_Patterns,
  KEYlist_Patterns,
  KEYappend_Patterns
} Patterns_KEY(Patterns);
extern Patterns copy_Patterns(Patterns);
extern void assert_Patterns(Patterns);

extern Patterns nil_Patterns();

extern Patterns list_Patterns(Pattern);
extern Pattern list_Patterns_elem(Patterns);

extern Patterns append_Patterns(Patterns,Patterns);
extern Patterns append_Patterns_l1(Patterns);
extern Patterns append_Patterns_l2(Patterns);

extern enum KEYTYPE_Formals {
  KEYnil_Formals,
  KEYlist_Formals,
  KEYappend_Formals
} Formals_KEY(Formals);
extern Formals copy_Formals(Formals);
extern void assert_Formals(Formals);

extern Formals nil_Formals();

extern Formals list_Formals(ValueDecl);
extern ValueDecl list_Formals_elem(Formals);

extern Formals append_Formals(Formals,Formals);
extern Formals append_Formals_l1(Formals);
extern Formals append_Formals_l2(Formals);

extern enum KEYTYPE_TypeFormals {
  KEYnil_TypeFormals,
  KEYlist_TypeFormals,
  KEYappend_TypeFormals
} TypeFormals_KEY(TypeFormals);
extern TypeFormals copy_TypeFormals(TypeFormals);
extern void assert_TypeFormals(TypeFormals);

extern TypeFormals nil_TypeFormals();

extern TypeFormals list_TypeFormals(TypeDecl);
extern TypeDecl list_TypeFormals_elem(TypeFormals);

extern TypeFormals append_TypeFormals(TypeFormals,TypeFormals);
extern TypeFormals append_TypeFormals_l1(TypeFormals);
extern TypeFormals append_TypeFormals_l2(TypeFormals);

extern enum KEYTYPE_Actuals {
  KEYnil_Actuals,
  KEYlist_Actuals,
  KEYappend_Actuals
} Actuals_KEY(Actuals);
extern Actuals copy_Actuals(Actuals);
extern void assert_Actuals(Actuals);

extern Actuals nil_Actuals();

extern Actuals list_Actuals(Expression);
extern Expression list_Actuals_elem(Actuals);

extern Actuals append_Actuals(Actuals,Actuals);
extern Actuals append_Actuals_l1(Actuals);
extern Actuals append_Actuals_l2(Actuals);

extern enum KEYTYPE_TypeActuals {
  KEYnil_TypeActuals,
  KEYlist_TypeActuals,
  KEYappend_TypeActuals
} TypeActuals_KEY(TypeActuals);
extern TypeActuals copy_TypeActuals(TypeActuals);
extern void assert_TypeActuals(TypeActuals);

extern TypeActuals nil_TypeActuals();

extern TypeActuals list_TypeActuals(Type);
extern Type list_TypeActuals_elem(TypeActuals);

extern TypeActuals append_TypeActuals(TypeActuals,TypeActuals);
extern TypeActuals append_TypeActuals_l1(TypeActuals);
extern TypeActuals append_TypeActuals_l2(TypeActuals);

extern enum KEYTYPE_PatternActuals {
  KEYnil_PatternActuals,
  KEYlist_PatternActuals,
  KEYappend_PatternActuals
} PatternActuals_KEY(PatternActuals);
extern PatternActuals copy_PatternActuals(PatternActuals);
extern void assert_PatternActuals(PatternActuals);

extern PatternActuals nil_PatternActuals();

extern PatternActuals list_PatternActuals(Pattern);
extern Pattern list_PatternActuals_elem(PatternActuals);

extern PatternActuals append_PatternActuals(PatternActuals,PatternActuals);
extern PatternActuals append_PatternActuals_l1(PatternActuals);
extern PatternActuals append_PatternActuals_l2(PatternActuals);

extern Program program(Units);
extern Units program_units(Program);

extern Unit no_unit();

extern Unit with_unit(String);
extern String with_unit_name(Unit);

extern Unit decl_unit(Declaration);
extern Declaration decl_unit_decl(Unit);

extern Declaration no_decl();

extern Declaration module_decl(SignatureDecl,TypeDecl,Declarations);
extern SignatureDecl module_decl_as_sig(Declaration);
extern TypeDecl module_decl_as_tfunc(Declaration);
extern Declarations module_decl_contents(Declaration);

extern Declaration signature_decl(SignatureDecl,Declaration,Declarations);
extern SignatureDecl signature_decl_as_sig(Declaration);
extern Declaration signature_decl_creating(Declaration);
extern Declarations signature_decl_contents(Declaration);

extern Declaration phylum_decl(TypeDecl,Type);
extern TypeDecl phylum_decl_as_type(Declaration);
extern Type phylum_decl_type_(Declaration);

extern Declaration constructor_decl(ValueDecl,PatternDecl,Declaration);
extern ValueDecl constructor_decl_as_value(Declaration);
extern PatternDecl constructor_decl_as_pattern(Declaration);
extern Declaration constructor_decl_body(Declaration);

extern Declaration attribute_decl(ValueDecl,Direction,Default);
extern ValueDecl attribute_decl_as_value(Declaration);
extern Direction attribute_decl_direction(Declaration);
extern Default attribute_decl_default(Declaration);

extern Declaration type_decl(TypeDecl,Type);
extern TypeDecl type_decl_as_type(Declaration);
extern Type type_decl_type_(Declaration);

extern Declaration function_decl(ValueDecl,Declaration);
extern ValueDecl function_decl_as_value(Declaration);
extern Declaration function_decl_body(Declaration);

extern Declaration procedure_decl(ValueDecl,Declaration);
extern ValueDecl procedure_decl_as_value(Declaration);
extern Declaration procedure_decl_body(Declaration);

extern Declaration top_level_match(Match);
extern Match top_level_match_m(Declaration);

extern Declaration value_decl(ValueDecl,Direction,Default);
extern ValueDecl value_decl_as_value(Declaration);
extern Direction value_decl_direction(Declaration);
extern Default value_decl_default(Declaration);

extern Declaration pattern_decl(PatternDecl,Pattern);
extern PatternDecl pattern_decl_as_pattern(Declaration);
extern Pattern pattern_decl_choices(Declaration);

extern Declaration inheritance(Type,Renamings);
extern Type inheritance_used(Declaration);
extern Renamings inheritance_renamings(Declaration);

extern Declaration pragma_decl(Symbol,Expressions);
extern Symbol pragma_decl_name(Declaration);
extern Expressions pragma_decl_parameters(Declaration);

extern Renaming no_renaming();

extern Renaming signature_replacement(Signature,Signature);
extern Signature signature_replacement_old(Renaming);
extern Signature signature_replacement_ew(Renaming);

extern Renaming type_replacement(Type,Type);
extern Type type_replacement_old(Renaming);
extern Type type_replacement_new(Renaming);

extern Renaming value_replacement(Expression,Expression);
extern Expression value_replacement_old(Renaming);
extern Expression value_replacement_new(Renaming);

extern Renaming pattern_replacement(Pattern,Pattern);
extern Pattern pattern_replacement_old(Renaming);
extern Pattern pattern_replacement_new(Renaming);

extern Renaming signature_renaming(SignatureDecl,Signature,Renamings);
extern SignatureDecl signature_renaming_decl(Renaming);
extern Signature signature_renaming_old(Renaming);
extern Renamings signature_renaming_elements(Renaming);

extern Renaming type_renaming(TypeDecl,Type);
extern TypeDecl type_renaming_decl(Renaming);
extern Type type_renaming_old(Renaming);

extern Renaming value_renaming(ValueDecl,Expression);
extern ValueDecl value_renaming_decl(Renaming);
extern Expression value_renaming_old(Renaming);

extern Renaming pattern_renaming(PatternDecl,Pattern);
extern PatternDecl pattern_renaming_decl(Renaming);
extern Pattern pattern_renaming_old(Renaming);

extern Direction no_direction(Boolean);
extern Boolean no_direction_is_input(Direction);

extern Direction collection_(Boolean);
extern Boolean collection__is_input(Direction);

extern Direction circular_(Boolean);
extern Boolean circular__is_input(Direction);

extern Default simple(Expression);
extern Expression simple_value(Default);

extern Default composite(Expression,Expression);
extern Expression composite_initial(Default);
extern Expression composite_combiner(Default);

extern Default lattice(Expression,Expression,Expression);
extern Expression lattice_bottom(Default);
extern Expression lattice_join(Default);
extern Expression lattice_equal(Default);

extern Default no_default();

extern SignatureDecl a_signature(Symbol,TypeFormals,Boolean,Boolean);
extern Symbol a_signature_name(SignatureDecl);
extern TypeFormals a_signature_type_formals(SignatureDecl);
extern Boolean a_signature_constant_(SignatureDecl);
extern Boolean a_signature_exported(SignatureDecl);

extern TypeDecl a_type(Symbol,TypeFormals,Signatures,Boolean,Boolean);
extern Symbol a_type_name(TypeDecl);
extern TypeFormals a_type_type_formals(TypeDecl);
extern Signatures a_type_signatures(TypeDecl);
extern Boolean a_type_constant_(TypeDecl);
extern Boolean a_type_exported(TypeDecl);

extern ValueDecl a_value(Symbol,TypeFormals,Type,Boolean,Boolean);
extern Symbol a_value_name(ValueDecl);
extern TypeFormals a_value_type_formals(ValueDecl);
extern Type a_value_type_(ValueDecl);
extern Boolean a_value_constant_(ValueDecl);
extern Boolean a_value_exported(ValueDecl);

extern PatternDecl a_pattern(Symbol,TypeFormals,Type,Boolean,Boolean);
extern Symbol a_pattern_name(PatternDecl);
extern TypeFormals a_pattern_type_formals(PatternDecl);
extern Type a_pattern_type_(PatternDecl);
extern Boolean a_pattern_constant_(PatternDecl);
extern Boolean a_pattern_exported(PatternDecl);

extern Type type_name(Symbol);
extern Symbol type_name_name(Type);

extern Type no_type();

extern Type type_inst(Type,TypeActuals,Actuals);
extern Type type_inst_base(Type);
extern TypeActuals type_inst_type_actuals(Type);
extern Actuals type_inst_actuals(Type);

extern Type qual_type(Type,Type);
extern Type qual_type_inst(Type);
extern Type qual_type_type_(Type);

extern Expression value_name(Symbol);
extern Symbol value_name_name(Expression);

extern Expression value_inst(Expression,TypeActuals);
extern Expression value_inst_base(Expression);
extern TypeActuals value_inst_actuals(Expression);

extern Expression qual_value(Type,Expression);
extern Type qual_value_inst(Expression);
extern Expression qual_value_value(Expression);

extern Signature sig_name(Symbol);
extern Symbol sig_name_name(Signature);

extern Signature no_sig();

extern Signature sig_inst(Signature,TypeActuals);
extern Signature sig_inst_sig(Signature);
extern TypeActuals sig_inst_actuals(Signature);

extern Signature qual_sig(Type,Signature);
extern Type qual_sig_inst(Signature);
extern Signature qual_sig_sig(Signature);

extern Pattern pattern_name(Symbol);
extern Symbol pattern_name_name(Pattern);

extern Pattern no_pattern();

extern Pattern pattern_inst(Pattern,TypeActuals);
extern Pattern pattern_inst_base(Pattern);
extern TypeActuals pattern_inst_actuals(Pattern);

extern Pattern qual_pattern(Type,Pattern);
extern Type qual_pattern_inst(Pattern);
extern Pattern qual_pattern_pattern(Pattern);

extern Signature var_sig(Signature);
extern Signature var_sig_sig(Signature);

extern Signature constant_sig(Signature);
extern Signature constant_sig_sig(Signature);

extern Signature module_sig(TypeFormals,Formals,Declaration);
extern TypeFormals module_sig_type_formals(Signature);
extern Formals module_sig_formals(Signature);
extern Declaration module_sig_return_type(Signature);

extern Signature fixed_sig(Types);
extern Types fixed_sig_types(Signature);

extern Type remote_type(Type);
extern Type remote_type_nodetype(Type);

extern Type ordered_set_type(Type,Expression,Expression);
extern Type ordered_set_type_u(Type);
extern Expression ordered_set_type_equal(Type);
extern Expression ordered_set_type_order(Type);

extern Type set_type(Type,Expression);
extern Type set_type_u(Type);
extern Expression set_type_equal(Type);

extern Type list_type(Type);
extern Type list_type_u(Type);

extern Type function_type(Formals,Declaration);
extern Formals function_type_formals(Type);
extern Declaration function_type_return_value(Type);

extern Pattern simple_pattern(Pattern,PatternActuals);
extern Pattern simple_pattern_con(Pattern);
extern PatternActuals simple_pattern_actuals(Pattern);

extern Pattern pattern_actual(Pattern,Expression);
extern Pattern pattern_actual_arg(Pattern);
extern Expression pattern_actual_formal(Pattern);

extern Pattern sequence_pattern(Patterns,Type);
extern Patterns sequence_pattern_actuals(Pattern);
extern Type sequence_pattern_type_(Pattern);

extern Pattern rest_pattern(Pattern);
extern Pattern rest_pattern_constraint(Pattern);

extern Pattern choice_pattern(Patterns);
extern Patterns choice_pattern_choices(Pattern);

extern Pattern and_pattern(Pattern,Pattern);
extern Pattern and_pattern_p1(Pattern);
extern Pattern and_pattern_p2(Pattern);

extern Pattern pattern_var(ValueDecl);
extern ValueDecl pattern_var_as_value(Pattern);

extern Pattern condition(Expression);
extern Expression condition_e(Pattern);

extern Declaration stmts(Declarations);
extern Declarations stmts_body(Declaration);

extern Declaration effect(Expression);
extern Expression effect_e(Declaration);

extern Declaration assign(Expression,Expression);
extern Expression assign_lhs(Declaration);
extern Expression assign_rhs(Declaration);

extern Declaration if_stmt(Expression,Declaration,Declaration);
extern Expression if_stmt_cond(Declaration);
extern Declaration if_stmt_if_true(Declaration);
extern Declaration if_stmt_if_false(Declaration);

extern Declaration for_in_stmt(ValueDecl,Expression,Declaration);
extern ValueDecl for_in_stmt_formal(Declaration);
extern Expression for_in_stmt_seq(Declaration);
extern Declaration for_in_stmt_body(Declaration);

extern Declaration for_on_stmt(ValueDecl,Expression,Declaration);
extern ValueDecl for_on_stmt_formal(Declaration);
extern Expression for_on_stmt_seq(Declaration);
extern Declaration for_on_stmt_body(Declaration);

extern Declaration for_stmt(Expression,Matches);
extern Expression for_stmt_expr(Declaration);
extern Matches for_stmt_matchers(Declaration);

extern Declaration case_stmt(Expression,Matches,Declaration);
extern Expression case_stmt_expr(Declaration);
extern Matches case_stmt_matchers(Declaration);
extern Declaration case_stmt_default(Declaration);

extern Match matcher(TypeFormals,Pattern,Declaration);
extern TypeFormals matcher_polymorphism(Match);
extern Pattern matcher_pat(Match);
extern Declaration matcher_stmt(Match);

extern Expression integer_const(String);
extern String integer_const_token(Expression);

extern Expression string_const(String);
extern String string_const_token(Expression);

extern Expression char_const(String);
extern String char_const_token(Expression);

extern Expression undefined();

extern Expression no_expr();

extern Expression funcall(Expression,Actuals);
extern Expression funcall_f(Expression);
extern Actuals funcall_actuals(Expression);

extern Expression reduce(Expression,Expressions);
extern Expression reduce_f(Expression);
extern Expressions reduce_elems(Expression);

extern Expression sequence(Expressions,Type);
extern Expressions sequence_elems(Expression);
extern Type sequence_type_(Expression);

extern Expression constructor_key(Expression);
extern Expression constructor_key_name(Expression);

extern Expression signature_value(Signature);
extern Signature signature_value_s(Expression);

extern Expression type_value(Type);
extern Type type_value_t(Expression);

extern Expression pattern_value(Pattern);
extern Pattern pattern_value_p(Expression);

extern Expression repeat(Expression);
extern Expression repeat_expr(Expression);

extern Expression guarded(Expression,Expression);
extern Expression guarded_expr(Expression);
extern Expression guarded_cond(Expression);

extern Expression controlled(Expression,ValueDecl,Expression);
extern Expression controlled_expr(Expression);
extern ValueDecl controlled_decl(Expression);
extern Expression controlled_set(Expression);

