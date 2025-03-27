# HW-频率原则上机作业
## 任务一:研究不同频率幅度对模型收敛速度的影响

运行代码main函数放在最后，选择15%作为误差

![a_ration](https://imgur.com/Ym9wFtp)

1. 第一阶段中ratio的下降或是因为初始的a很小，**高频分量不明显**，导致需要很长的step去检测，随着a的增大，高频分量更容易被检测到，从而导致step的降低，即ratio的下降。
2. 第二阶段中ratio逐渐上升，这符合频率原则，一定程度上对其进行了验证。

## 任务二：研究不同高频对模型收敛速度的影响

运行代码main函数放在最后，选择20%作为误差

![k_ration](https://imgur.com/thPwzqU)

随着k的增加，ratio逐渐增大，说明需要更大的step去收敛，验证了频率原则。

---
###任务一代码：
~~~
act_func = get_act_func(args.act_func_name)
loss_fn = nn.MSELoss(reduction='mean')

# List of a values to test
a_list = [0.25, 0.5, 1.5, 2, 2.5, 3, 3.5, 4, 4.5, 5]
ratios = []

for a in a_list:
    print(f"\nTraining for a = {a}")
    # Define target function for this a
    def target_func(x):
        return torch.sin(x) + a * torch.sin(4 * x)
    
    # Generate dataset
    args.training_input, args.training_target, args.test_input, args.test_target = get_dataset(args, target_func)
    
    # Initialize model and optimizer
    model = Model(args.t, args.hidden_layers_width, args.input_dim, args.output_dim, act_func).to(args.device)
    optimizer = torch.optim.Adam(model.parameters(), lr=args.lr) if args.optimizer == 'adam' else torch.optim.SGD(model.parameters(), lr=args.lr)
    
    # Variables to track convergence steps
    step_low = None
    step_high = None
    t0 = time.time()
    
    # Training loop
    for epoch in range(args.epochs + 1):
        loss, training_output = train_one_step(model, optimizer, loss_fn, args)
        loss_test, output = test(model, loss_fn, args)
        
        # Compute frequency projections
        p1, p4 = compute_projections(training_output, args.training_input)
        err_low = abs(p1 - 1)  # Low-frequency error
        err_high = abs(p4 - a) / a  # High-frequency error
        
        # Record steps when errors fall below 15%
        if step_low is None and err_low < 0.15:
            step_low = epoch
        if step_high is None and err_high < 0.15:
            step_high = epoch
        
        # Print progress
        if epoch % args.plot_epoch == 0:
            print(f"Epoch {epoch}, Loss: {loss:.6f}, Err Low: {err_low:.6f}, Err High: {err_high:.6f}, Time: {(time.time() - t0):.2f} s")
    
    # Compute and store ratio
    if step_low is not None and step_high is not None:
        ratio = step_high / step_low if step_low != 0 else float('inf')
        print(f"a={a}, step_low={step_low}, step_high={step_high}, ratio={ratio}")
        ratios.append(ratio)
    else:
        print(f"a={a}, did not converge within {args.epochs} epochs")
        ratios.append(None)

# Plot a vs ratio
plt.figure()
plt.plot(a_list, ratios, 'o-', label='Ratio')
plt.xlabel('a')
plt.ylabel('Ratio (steps_high / steps_low)')
plt.title('Influence of a on Convergence Speed')
plt.grid(True)
plt.legend()
plt.savefig(os.path.join(args.path, 'a_vs_ratio.png'), dpi=300)
plt.show()
~~~

### 任务二代码：
~~~
act_func = get_act_func(args.act_func_name)
loss_fn = nn.MSELoss(reduction='mean')

# List of k values to test
k_list = [0.1, 0.5, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
ratios = []

for k in k_list:
    print(f"\nTraining for k = {k}")
    # Define target function for this k
    def target_func(x):
        return torch.sin(x) + 0.2 * torch.sin(k * x)
    
    # Generate dataset
    args.training_input, args.training_target, args.test_input, args.test_target = get_dataset(args, target_func)
    
    # Check projections on true function (sanity check)
    p1_true, p_k_true = compute_projections(args.training_target, args.training_input, k)
    print(f"True projections: p1 = {p1_true:.6f}, p_k = {p_k_true:.6f}")
    
    # Initialize model and optimizer
    model = Model(args.t, args.hidden_layers_width, args.input_dim, args.output_dim, act_func).to(args.device)
    optimizer = torch.optim.Adam(model.parameters(), lr=args.lr) if args.optimizer == 'adam' else torch.optim.SGD(model.parameters(), lr=args.lr)
    
    # Variables to track convergence steps
    step_low = None
    step_high = None
    t0 = time.time()
    
    # Training loop
    for epoch in range(args.epochs + 1):
        loss, training_output = train_one_step(model, optimizer, loss_fn, args)
        # Compute projections
        p1, p_k = compute_projections(training_output, args.training_input, k)
        err_low = abs(p1 - 1)  # True amplitude of sin(x) is 1
        err_high = abs(p_k - 0.2) / 0.2  # True amplitude of sin(k*x) is 0.2
        
        # Record steps when errors fall below 10%
        if step_low is None and err_low < 0.2:
            step_low = epoch
        if step_high is None and err_high < 0.2:
            step_high = epoch
        
        # Print progress
        if epoch % args.plot_epoch == 0:
            print(f"Epoch {epoch}, Loss: {loss:.6f}, Err Low: {err_low:.6f}, Err High: {err_high:.6f}, Time: {(time.time() - t0):.2f} s")
    
    # Compute and store ratio
    if step_low is not None and step_high is not None:
        ratio = step_high / step_low if step_low != 0 else float('inf')
        print(f"k={k}, step_low={step_low}, step_high={step_high}, ratio={ratio:.4f}")
        ratios.append(ratio)
    else:
        print(f"k={k}, did not converge within {args.epochs} epochs")
        ratios.append(None)

plt.figure()
plt.plot(k_list, ratios, 'o-', label='Ratio (steps_high / steps_low)')
plt.xlabel('k')
plt.ylabel('Ratio')
plt.title('Influence of Frequency k on Convergence Speed')
plt.grid(True)
plt.legend()
plt.savefig(os.path.join(args.path, 'k_vs_ratio.png'), dpi=300)
plt.show()
print(args.path)
~~~
