Measuring LLM Self-Edit Resistance Through Writing Behavior
04/12/2026

### Co-authors:
Terra Jiang (yjiang66@berkeley.edu)
Matilda Orona (matilda_orona@berkeley.edu)
Rahil Sharma (rahilsharma@berkeley.edu)


### Abstract:
This paper investigates self-preference bias in Large Language
Models (LLMs) through the behavioral metric of self-edit
resistance. While prior research has shown that LLM
evaluators favor their own writings, we examine whether this
bias also manifests during generative rewriting. We expanded
the Human ChatGPT Comparison Corpus (HC3) by
generating responses from four recent models (GPT-5 mini,
Claude Haiku 4.5, Gemini 2.5 Flash, and Kimi K2) across
5,306 questions and then had each model rewrite every
model’s output. Our investigation proceeds in three stages.
First, we fine-tune four encoder models, BERT-base,
DeBERTa-base, ModernBERT-base, and Ettin-Encoder-400m,
on authorship attribution, authorship persistence, and rewriter
identification tasks, achieving near-perfect accuracy across all
experiments. Second, we quantify editing behavior through
five complementary metrics: Levenshtein distance, BLEU,
ROUGE-L, BERTScore, and sentence-transformer cosine
similarity, which are aggregated into a combined Self-Edit
Resistance Score (SERS). Third, we train a gradient-boosted
classifier using only these five metrics to distinguish self-pairs
from cross-pairs. Our results show that GPT-5 mini and
Gemini 2.5 Flash exhibit strong self-edit resistance, Claude
Haiku 4.5 rewrites more uniformly, and Kimi K2 reverses the
pattern by aggressively rewriting even its own text. These
findings establish self-edit resistance as a model-specific
behavioral signature and a promising signal for model source
attribution.