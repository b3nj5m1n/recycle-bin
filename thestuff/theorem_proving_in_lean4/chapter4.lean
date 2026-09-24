section
  variable (α : Type) (r : α → α → Prop)
  variable (refl_r : ∀ {x}, r x x)
  variable (symm_r : ∀ {x y}, r x y → r y x)
  variable (trans_r : ∀ {x y z}, r x y → r y z → r x z)

  variable (a b c : α)
  variable (hab : r a b) (hbc : r b c)

  #check trans_r
  #check @trans_r a b c
  #check trans_r hab
  #check trans_r hab hbc

  variable (hcb : r c b)
  #check symm_r hcb

  example (a b c d : α) (hab : r a b) (hcb : r c b) (hcd : r c d) : r a d :=
    trans_r (trans_r hab (symm_r hcb)) hcd

  #check Sort 4


  #check Eq.refl
  #check Eq.symm
  #check Eq.trans

  universe u

  #check @Eq.refl.{u}

  example (a b c d : α) (hab : a = b) (hcb : c = b) (hcd : c = d) : Eq a d :=
    Eq.trans (Eq.trans hab (Eq.symm hcb)) hcd
end

section
  variable (α: Type)
  variable (a b : α)
  variable (f g : α → Nat)
  variable (h₁ : a = b)
  variable (h₂ : f = g)

  example : f a = f b := congrArg f h₁
  example : f a = g a := congrFun h₂ a
  example : f a = g b := congr h₂ h₁

  example (x y : Nat) :
      (x + y) * (x + y) = x * x + y * x + x * y + y * y :=
    have h₁ : (x+y) * (x+y) = (x+y) * x + (x+y) * y :=
      Nat.mul_add (x+y) x y
    have h₂ : (x+y) * (x+y) = x*x + y*x + (x*y + y*y) :=
      (Nat.add_mul x y x) ▸ (Nat.add_mul x y y) ▸ h₁
    h₂.trans (Nat.add_assoc (x*x + y*x) (x*y) (y*y)).symm
end

section
  variable (a b c d e : Nat)

  theorem T
      (h₁ : a = b)
      (h₂ : b = c + 1)
      (h₃ : c = d)
      (h₄ : e = 1 + d) :
      a = e :=
    calc
      a = b   := h₁
      _ = c + 1 := h₂
      _ = d + 1 := congrArg Nat.succ h₃
      _ = 1 + d := Nat.add_comm d 1
      _ = e     := Eq.symm h₄


  example (h₁ : a = b) (h₂ : b ≤ c) (h₃ : c + 1 < d) : a < d :=
    calc
      a = b := h₁
      _ ≤ c := h₂
      _ < c + 1 := Nat.lt_succ_self c
      _ < d := h₃
end



section
  def divides (x y : Nat) : Prop :=
    ∃ k, k * x = y

  theorem divides_trans (h₁ : divides x y) (h₂ : divides y z) : divides x z :=
    let ⟨k₁, d₁⟩ := h₁
    let ⟨k₂, d₂⟩ := h₂
    ⟨k₁ * k₂, by rw [Nat.mul_comm k₁ k₂, Nat.mul_assoc, d₁, d₂]⟩

  theorem divides_mul (x : Nat) (k : Nat) : divides x (k*x) :=
    ⟨k, rfl⟩

  instance : Trans divides divides divides where
    trans := divides_trans

  example (h₁ : divides x y) (h₂ : y = z) : divides x (2*z) :=
    calc
      divides x y := h₁
      _ = z := h₂
      divides _ (2*z) := divides_mul z 2
end


section
  example : ∃ x : Nat, x > 0 :=
    have h : 1 > 0 := Nat.zero_lt_succ 0
    ⟨1,h⟩

  example (x : Nat) (h : x > 0) : ∃ y, y < x :=
    ⟨0, h⟩

  example (x y z : Nat) (hxy : x < y) (hyz : y < z) : ∃ w, x < w ∧ w < z :=
    ⟨y,⟨hxy, hyz⟩⟩
end

section
  variable (p q : α → Prop)

  example (h : ∃ x, p x ∧ q x) : ∃ x, q x ∧ p x :=
    Exists.elim h
    (λ w => λ hw : p w ∧ q w => show ∃ x, q x ∧ p x from ⟨w, hw.right, hw.left⟩)

  example (h : ∃ x, p x ∧ q x) : ∃ x, q x ∧ p x :=
    match h with
    | Exists.intro w (And.intro hp hq) => show ∃ x, q x ∧ p x from ⟨w, hq, hp⟩

  example (h : ∃ x, p x ∧ q x) : ∃ x, q x ∧ p x :=
    match h with
    | ⟨w, hp, hq⟩ => show ∃ x, q x ∧ p x from ⟨w, hq, hp⟩

  example (h : ∃ x, p x ∧ q x) : ∃ x, q x ∧ p x :=
    let ⟨w, hp, hq⟩ := h
    show ∃ x, q x ∧ p x from ⟨w, hq, hp⟩

  example : (h : ∃ x, p x ∧ q x) → ∃ x, q x ∧ p x :=
    λ ⟨w, hp, hq⟩ => ⟨w, hq, hp⟩
end

section
  def isEven (x : Nat) := ∃ k, x=2*k

  theorem even_plus_even (h₁ : isEven a) (h₂ : isEven b) : isEven (a+b) :=
    let ⟨k₁, h₁⟩ := h₁
    let ⟨k₂, h₂⟩ := h₂
    ⟨k₁ + k₂, (
      calc a + b
        _ = 2*k₁ + b := by rw[h₁]
        _ = 2*k₁ + 2*k₂ := by rw[h₂]
        _ = 2*(k₁ + k₂) := by rw[Nat.mul_add]
    )⟩
end


section
  open Classical
  variable (p : α → Prop)

  example (h : ¬ ∀ x, ¬ p x) : ∃ x, p x :=
    byContradiction (λ hnx : ¬ ∃ x, p x =>
      have h2 : ∀ x, ¬ p x :=
        λ x =>
        λ h3 : p x =>
        have h4 : ∃ x, p x := ⟨x, h3⟩
        show False from hnx h4
      show False from h h2
      )
end

section existential_crisis
  variable (α : Type) (p q : α → Prop)
  variable (r : Prop)

  example : (∃ x : α, r) → r := λ ⟨_, h⟩ => h
  example (a : α) : r → (∃ x : α, r) := λ hr : r => ⟨a, hr⟩
  example : (∃ x, p x ∧ r) ↔ (∃ x, p x) ∧ r :=
    ⟨
      λ (⟨x, h⟩ : ∃ x, p x ∧ r) => ⟨⟨x, h.left⟩, h.right⟩,
      λ (⟨⟨x, h⟩, hr⟩ : ( ∃ x, p x ) ∧ r) => ⟨x, h, hr⟩
    ⟩
  example : (∃ x, p x ∨ q x) ↔ (∃ x, p x) ∨ (∃ x, q x) := sorry

  open Classical

  example : (∀ x, p x) ↔ ¬ (∃ x, ¬ p x) :=
    ⟨
      λ h : ∀ x, p x => byContradiction
        (λ h₁ : ¬ ¬ (∃ x, ¬ p x) =>
        have h₂ : ∃ x, ¬ p x := Classical.not_not.mp h₁
        let ⟨x, hpx⟩ := h₂
        show False from hpx (h x)),
      λ h : ¬ (∃ x, ¬ p x) => (λ x => byContradiction
        (λ h₁ : ¬ p x => show False from h ⟨x, h₁⟩))
    ⟩
  example : (∃ x, p x) ↔ ¬ (∀ x, ¬ p x) :=
    ⟨
      λ ( ⟨x, hx⟩ : ∃ x, p x ) => byContradiction
        λ h₁ : ¬ ¬ (∀ x, ¬ p x) =>
        have h₂ : ∀ x, ¬ p x := Classical.not_not.mp h₁
        show False from (h₂ x) hx,
      λ h : ¬ (∀ x, ¬ p x) => byContradiction
        λ h₁ : ¬ (∃ x, p x) => h (λ x => byContradiction
         (λ hnx : ¬ ¬ p x =>
           have h₂ : p x := Classical.not_not.mp hnx
           h₁ ⟨x, h₂⟩
         )),
    ⟩
  example : (¬ ∃ x, p x) ↔ (∀ x, ¬ p x) := sorry
  example : (¬ ∀ x, p x) ↔ (∃ x, ¬ p x) := sorry

  example : (∀ x, p x → r) ↔ (∃ x, p x) → r := sorry
  example (a : α) : (∃ x, p x → r) ↔ (∀ x, p x) → r := sorry
  example (a : α) : (∃ x, r → p x) ↔ (r → ∃ x, p x) := sorry
end existential_crisis

section Exercises1
  variable (α : Type) (p q : α → Prop)

  example : (∀ x, p x ∧ q x) ↔ (∀ x, p x) ∧ (∀ x, q x) := sorry
  example : (∀ x, p x → q x) → (∀ x, p x) → (∀ x, q x) := sorry
  example : (∀ x, p x) ∨ (∀ x, q x) → ∀ x, p x ∨ q x := sorry
end Exercises1

section Exercises2
  variable (α : Type) (p q : α → Prop)
  variable (r : Prop)

  example : α → ((∀ x : α, r) ↔ r) := sorry
  example : (∀ x, p x ∨ r) ↔ (∀ x, p x) ∨ r := sorry
  example : (∀ x, r → p x) ↔ (r → ∀ x, p x) := sorry
end Exercises2

section Exercises3
  variable (men : Type) (barber : men)
  variable (shaves : men → men → Prop)

  example (h : ∀ x : men, shaves barber x ↔ ¬ shaves x x) : False :=
    sorry
end Exercises3

section Exercises4
  def even (n : Nat) : Prop := ∃ k, n = 2*k

  def prime (n : Nat) : Prop := n > 1 ∧ ∀ k, k ∣ n → k = 1 ∨ k = n

  def infinitely_many_primes : Prop := ∀ n : Nat, ∃ p : Nat, p ≥ n ∧ prime p

  def Fermat_prime (n : Nat) : Prop := ∃ k : Nat, n = Pow.pow 2 (Pow.pow 2 k) + 1 ∧ prime n

  def infinitely_many_Fermat_primes : Prop :=  ∀ n : Nat, ∃ p : Nat, p ≥ n ∧ Fermat_prime p

  def goldbach_conjecture : Prop := ∀ n : Nat, n > 2 ∧ even n → ∃ p₁ p₂ : Nat, n = p₁ + p₂ ∧ prime p₁ ∧ prime p₂

  def Goldbach's_weak_conjecture : Prop := ∀ n : Nat, n > 5 ∧ ¬ even n → ∃ p₁ p₂ p₃ : Nat, n = p₁ + p₂ + p₃ ∧ prime p₁ ∧ prime p₂ ∧ prime p₃

  def Fermat's_last_theorem : Prop := ∀ k : Nat, k > 2 → ¬ ∃ a b c : Nat, a ≠ 0 ∧ b ≠ 0 ∧ c ≠ 0 ∧ Pow.pow a k = Pow.pow b k + Pow.pow c k
end Exercises4
